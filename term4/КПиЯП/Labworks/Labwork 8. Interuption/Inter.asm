.model tiny 
.code
org 100h
start:       
    jmp handlerInstall  
    
    	flag 					db "Grabber"
    
    ;interuptions
    	returnOldInteruptFlag   db 0
        originalIRQ0 			dd ?
    	originalIRQ1 			dd ? 
    	
    ;command line things 
    	keyCode db 0 
      	saveFlag db 0   
    	rawBufer db srceenWidth dup (?)
        superThing db 0Ah  
        srceenWidth equ 80  
   	 	screenHeight equ 25
    
    ;file 
    	fileName db 125 dup (?)
        fileDescriptor dd ? 
      
    ;DOS string 
        incorrectCommandLineParametersString db "Inccorrect command line parameters:", 0Dh, 0Ah, "[executable name] [save file name path]", '$'
       
        fileCreationError 					db "Couldn't create a file with this name", 0Dh, 0Ah, '$'
       
	    pressKeyString						db "Press the key (not 'Q') you want to use to grab the console.", 0Dh, 0Ah, '$' 
	    keyPressedString					db "Press Control + this key to grab console", 0Dh, 0Ah, "Press Control + 'Q' to quit the resident program.", 0Dh, 0Ah, '$'   
	    QKeyPressedString					db "'Q' cannot be used, as it is reserved for exiting the program.", 0Dh, 0Ah, '$'
	    
	    programAlreadyInMemoryString  		db "This resident program is already in memory.", 0Dh, 0Ah, '$' 
	 
	 ;BIOS strings       
	    interuptionsReturnStringLenght   	equ 49
	    interuptionsReturnString        	db 0Dh, 0Ah, "Original interruptions returned successfully.", 0Dh, 0Ah
		
		fileOpenErrorStringLenght 			equ 27
		fileOpenErrorString					db 0Dh, 0Ah, "Error in save proccess!", 0Dh, 0Ah	    
	    
	    grabStringLenght 					equ 9
		grabString							db 0Dh, 0Ah, "Grab!", 0Dh, 0Ah	

macro readStringFrom pointer
    mov ah, 09h  
    lea dx, pointer 
    int 21h
endm  

macro insertMessageInVideoMemory message, lenght  
	mov ax, cs
	mov es, ax
	mov ah, 03h
	mov bh, 0
	int 10h 								;get cursor position
	
	mov ah, 13h
	mov al, 00000001b						;draw mode 
	mov bh, 0                               
	mov bl, 07h                             ;attribute
	mov cx, lenght                          
	lea bp, message
	int 10h  								;print interuption return message
endm

    
IRQ0 proc far
		pusha
	    push ds
	    push es
	        
	    mov ax, cs
	    mov ds, ax 
	        
	    cmp saveFlag, 1
	    je saveCMD
	        
	    cmp returnOldInteruptFlag, 1 
	    je returnInteruptions
        
        jmp IRQ0End
         
         
        saveCMD:  
	    	mov cs:saveFlag, 0  
			openFile:
				mov ah, 3dh
				mov al, 00000001b	
				lea dx, fileName 
				cli  
				int 21h  
				sti
				jc fileOpenError
				
				mov fileDescriptor, ax
				jmp grabConsole
			    
			    fileOpenError: 
			    	insertMessageInVideoMemory fileOpenErrorString, fileOpenErrorStringLenght
                	mov cs:returnOldInteruptFlag, 1
                	jmp IRQ0End  
                	
                	
			grabConsole:
				mov ax, 0B800h
		        mov es, ax 
	
				mov di, 0
				mov cx, screenHeight  
				getCLLoop:	
					push cx	 
					lea si, rawBufer
					lea dx, rawBufer 
					mov cx, srceenWidth
					getRawLoop:  
						
						mov al, es:di
						mov [si], al
						inc si
						add di, 2
				    loop getRawLoop
		       			mov ah, 40h 
		       			mov bx, fileDescriptor
		       			mov cx, srceenWidth 
		       			inc cx
		       			lea dx, rawBufer
		       			int 21h	 
			     
			     pop cx
		         loop getCLLoop
		         
		         closeFile:
					mov ah, 3Eh
					mov bx, fileDescriptor
					cli
					int 21h
					sti	
					
		        	insertMessageInVideoMemory grabString, grabStringLenght  
		        	
		    	jmp IRQ0End 			
	      
	        returnInteruptions: 
	        	installOldInteruptionsAddressed: 
			        mov ah, 25h                			  	 
			        mov al, 08h                      		
			        mov dx, word ptr cs:originalIRQ0      
			        mov ds, word ptr cs:originalIRQ0 + 2  
			        int 21h                                	;install original IRQ0 interuption address   
		        
			        mov ah, 25h
			        mov al, 09h                     
			        mov dx, word ptr cs:originalIRQ1
			        mov ds, word ptr cs:originalIRQ1 + 2 	;install original IRQ1 interuption address   
			        int 21h                    				
		        
		        printInteruptionMessage:                                      	
					insertMessageInVideoMemory interuptionsReturnString, interuptionsReturnStringLenght
    IRQ0End: 
        pushf
        call cs:dword ptr originalIRQ0
        pop es
        pop ds
        popa 
        iret 
IRQ0 endp
    
IRQ1 proc far 
        pusha
        pushf
        call cs:dword ptr originalIRQ1
        
        mov ah, 01h
        int 16h			;check bufer   
        jz IRQ1end 		;no symbol   

         
        mov dh, ah		;scan-code in DH 
        
        mov ah, 02h
        int 16h   
        and al, 4		;control check
        cmp al, 0	
        jne checkExecuteKey  
        jmp IRQ1end 	;no contrl
        
    checkExecuteKey:        
        cmp dh, cs:keyCode	
        jne checkQ   
   
        mov cs:saveFlag, 1
        mov ah, 00h
        int 16h     
      
        jmp IRQ1end
        
    checkQ:
        cmp dh, 10h 
        jne IRQ1end
        mov cs:returnOldInteruptFlag, 1 
        
        mov ah, 00h
        int 16h 		;clean this letter
    IRQ1end:
        popa 
        iret 
IRQ1 endp


handlerInstall: 
		getCommandLineParameters:
			mov ch, 0
		    mov cl, [0080h]    ;CL size
		    
		    cmp cl, 1
		    jbe noParamError
		                      
		    mov si, 81h            ;comand line text begining
		   	lea di, fileName
		    getInfoLoop:
		        spaceCheck:
		            cmp [si], ' '
		            je spaceFound
		        
		        	movsb 
		            jmp endGetInfoLoop
		            
		        spaceFound:
		        	inc si
		            
		     	endGetInfoLoop:
			loop getInfoLoop
			
		
		
		createFile:
				mov ah, 3Ch
				mov cx, 00000000b 
				lea dx, fileName    
				int 21h 
			
			jc cantCreateFile
				
			mov fileDescriptor, ax  
				
			closeNewFile:
				mov ah, 3Eh
				mov bx, fileDescriptor
				int 21h
		    		
        readStringFrom pressKeyString
        
        getExecuteKeyCode:
        	mov ah, 00h
        	int 16h
        	
        	cmp ah, 10h
        	je Qpressed
        	jmp gotKey
		    	
		    Qpressed:
		        readStringFrom QKeyPressedString 
		    	jmp handlerInstall    
		    	
			gotKey:
				mov keyCode, ah 
				readStringFrom keyPressedString	
		    
        
        
        getOriginalInterruptionsAddresses:       
            mov ah, 35h
        	mov al, 09h  ; prerivaniye ot claviaturi
        	int 21h   
        	
        	mov word ptr originalIRQ1, bx
        	mov word ptr originalIRQ1 + 2, es   
        
	        mov ah, 35h 
	        mov al, 08h 
	        int 21h 							;get interruption address  
	        
	        mov word ptr originalIRQ0, bx
	        mov word ptr originalIRQ0 + 2, es  	;save interruption address 
	    
	    checkAlreadyLoaded:
	        lea di,   flag      
	        lea si,   flag
	        mov cx, 7
	       	repe cmpsb  
	        je loaded  
        
        setOwnInterruptions:
            mov ah, 25h
	        mov al, 09h
	        mov dx, offset IRQ1
	        int 21h 
        	
	        mov ah, 25h
	        mov al, 08h 
	        mov dx, offset IRQ0
	        int 21h
	       
        stayResident:
	        mov ah, 31h
	        mov dx, (handlerInstall - start + 10Fh) / 16 
	        int 21h
        
        noParamError:
            readStringFrom incorrectCommandLineParametersString 
            jmp handlerInstallEnd
        cantCreateFile:
		    readStringFrom fileCreationError 
		    jmp handlerInstallEnd
        loaded:
			readStringFrom programAlreadyInMemoryString 
			jmp handlerInstallEnd
			
    handlerInstallEnd:
        mov ax, 4Ch
        int 21h                           
end start