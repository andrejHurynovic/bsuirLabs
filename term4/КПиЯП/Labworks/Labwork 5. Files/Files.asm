.model small
.stack 100h
.data    

lines dw 1  
numberString db "     $"

maximalFilePathLenght equ 100h
filePath db maximalFilePathLenght dup (0) 
fileDescriptor dw 0

buferPointer dw 0
bufer db maximalBuferSize dup (0)
maximalBuferSize equ 100h 
currentBuferSize dw 0
    
maximalSearchWordLenght equ 50 
searchWord db maximalSearchWordLenght dup (0)
searchWordLenght dw 0  
foundWord db 0

lastOperation db 0 
lastSymbol db 0  
inNewLineSearch db 0 
  
            
            
;errors    
linesString 				db "Number of lines without this word: ", '$'
wordTooBigError 			db "Word size is bigger than 50!", 0Dh, 0Ah, '$'  
pharamError  				db "Parameters error!", 0Dh, 0Ah, '$'       
unknownErrorMsg          	db "Unknown error accured", 0Dh, 0Ah, '$'
operationErrorMsg        	db "Operation error", 0Dh, 0Ah, '$'
fileNotFoundMsg          	db "File not found", 0Dh, 0Ah, '$'
pathNotFoundMsg          	db "Path not found", 0Dh, 0Ah, '$'
tooManyFilesAreOpenedMsg 	db "Too many files are opened", 0Dh, 0Ah, '$'
accessIsDeniedMsg        	db "Access is denied", 0Dh, 0Ah, '$'
invalidAccessModeMsg     	db "Invalid access mode", 0Dh, 0Ah, '$'            

proc getInfoFromComandLine 
	mov ax, @data
	mov es, ax
	mov cl, ds:[0080h]
	mov ch, 0
	mov es:currentBuferSize, cx    
	
	cmp cl, 3
	jbe noParamError
	
	mov si, 81h  
	mov es:buferPointer, 0
	
	skipToWordLoop:     
		mov cx, es:currentBuferSize
		cmp es:buferPointer, cx
		je reachedEnd
		
		cmp [si], ' ' 
		jne exitSkipToWordLoop
		inc si
		inc es:buferPointer 
		jmp skipToWordLoop
	
	exitSkipToWordLoop: 
		;inc si
		;inc es:buferPointer 
	lea di, searchWord
	
	moveWordToSearchString:
	    mov cx, es:currentBuferSize
		cmp es:buferPointer, cx
		je reachedEnd
	 
		movsb 
		cmp [si], ' ' 
		je exitMoveWordToSearchString
		inc es:buferPointer 
		inc es:searchWordLenght 
	jmp moveWordToSearchString  
	
	exitMoveWordToSearchString:
	inc es:searchWordLenght
	cmp es:searchWordLenght, maximalSearchWordLenght
	je wordTooBig 
	
		inc si
		inc es:buferPointer 
		lea di, filePath
	
	moveFilePathToSearchString: 
		cmp [si], 0Dh
		je reachedCurrectlyEnd 
	    mov cx, es:currentBuferSize
		cmp es:buferPointer, cx
		je reachedCurrectlyEnd
	 
		movsb 
		inc es:buferPointer 
	jmp moveFilePathToSearchString  
	
	reachedCurrectlyEnd:
		mov es:[di], 0 
		jmp getInfoFromComandLineReturn
	
	wordTooBig: 
		mov ax, es
		mov ds, ax
	    readStringFrom wordTooBigError
		call exitProgram
	
	reachedEnd:
		mov ax, es
		mov ds, ax
	    readStringFrom pharamError
	    call exitProgram 
	    
	noParamError:
		mov ax, es
		mov ds, ax
		readStringFrom pharamError
		call exitProgram  
		
	getInfoFromComandLineReturn:	
		ret
endp getInfoFromComandLine

macro readStringFrom pointer  
	mov al, 00h
	mov ah, 09h
    lea dx, pointer 

    int 21h
endm     

proc initDataAndExtendedSegments
   	mov ax, @data
   	mov ds, ax
   	mov es, ax     
   	
   	mov currentBuferSize, 0
	
	ret	
endp initDataAndExtendedSegments

proc exitProgram
	mov ah, 3Eh
	mov bx, fileDescriptor
	int 21h	
	
	mov ah, 4ch
	mov al, 00h
	int 21h
	ret 
endp exitProgram  

proc openFile
	mov ah, 3dh
	mov al, 00000010b	
	lea dx, filePath   
	int 21h          
	
	jae okey 
	       
	fileError:  
	push ax	
	mov ax, @data
	mov ds, ax
	pop ax            
	
    cmp ax, 01h
        je operationError
    cmp ax, 02h
        je fileNotFound
    cmp ax, 03h
        je pathNotFound
    cmp ax, 04h
        je tooManyFilesAreOpened
    cmp ax, 05h
        je accessIsDenied
    cmp ax, 0Ch
        je invalidAccessMode
	
	
    readStringFrom unknownErrorMsg
    call exitProgram

operationError:
    readStringFrom operationErrorMsg
    call exitProgram
    
fileNotFound:
    readStringFrom fileNotFoundMsg
    call exitProgram
    
pathNotFound:
    readStringFrom pathNotFoundMsg
    call exitProgram
    
tooManyFilesAreOpened:
    readStringFrom tooManyFilesAreOpenedMsg
    call exitProgram 
    
accessIsDenied:
    readStringFrom accessIsDeniedMsg
    call exitProgram  
    
invalidAccessMode:
    readStringFrom invalidAccessModeMsg
    call exitProgram                       
	
	
	okey:  
	
	
	mov fileDescriptor, ax
	ret
endp openFile

proc emptyFileCheck
	cmp ax, 0
	je emptyFile
	ret
	
	emptyFile: 
	mov lines, 0
	call showResults	
endp emptyFileCheck

proc readFile
	mov ah, 3fh
	mov bx, fileDescriptor
	mov cx, maximalBuferSize
	sub cx, currentBuferSize
	lea dx, bufer  
	add dx, currentBuferSize
	int 21h   
	
	call emptyFileCheck
	                       
	add currentBuferSize, ax
	
	cmp cx, ax
	je fileEndDidntReached

	fileEndReached:  
		mov lastOperation, 1 
	
	fileEndDidntReached:
		ret
endp readFile	

proc loadNextSymbols 
	call findLastWordBegining
    
    mov cx, currentBuferSize 
    sub cx, buferPointer
    mov currentBuferSize, cx 
    
    
    lea di, bufer
    mov si, di
    add si, buferPointer   
    
    rep movsb    
    
    mov buferPointer, 0
	
	call readFile
	ret	
endp 



proc compareWords 
	mov ax, buferPointer
	cmp ax, currentBuferSize
	je lastSymbolInCompare
	
	lea di, searchWord
	push buferPointer
	push si
	
	mov cx, searchWordLenght
	
	repe cmpsb
	jne noWordInCompare
	
	foundWordInCompare:
		mov foundWord, 1 
		mov cx, searchWordLenght
		add buferPointer, cx 
		add sp, 4
		ret
	noWordInCompare:
		pop si
		pop buferPointer
		ret   
	lastSymbolInCompare:
		mov lastSymbol, 1  
		ret
endp compareWords	  

proc skipToNewLine 
	skipToNewLineLoop:
		mov ax, buferPointer
		cmp ax, currentBuferSize
		je lastSymbolInNewLineWord
		
		mov al, [si]
		
		cmp al, 0Ah
		je foundNewLineInNewLineWord 
	
	    inc si
	    inc buferPointer
	    
	    jmp skipToNewLineLoop

	foundNewLineInNewLineWord:
		inc lines   
		inc si
		inc buferPointer    
		mov inNewLineSearch, 0
	    ret
	
	lastSymbolInNewLineWord:
		mov lastSymbol, 1 
		ret
	ret
endp skipToNewLine  

proc skipToNextWord
	skipToNextWordLoop:
		mov ax, buferPointer
		cmp ax, currentBuferSize
		je lastSymbolInNextWord
		
		mov al, [si]
		
		cmp al, 20h  
		je foundSpaceInNextWord
		
		cmp al, 0Ah
		je foundNewLineInNextWord 
	    
	    cmp al, 09h  
	    je foundSpaceInNextWord
	    
	    inc si
	    inc buferPointer
	    
	    jmp skipToNextWordLoop
	    
	foundSpaceInNextWord:
		inc si
		inc buferPointer
		ret
	foundNewLineInNextWord:
		inc lines   
		inc si
		inc buferPointer
	    ret
	
	lastSymbolInNextWord:
		mov lastSymbol, 1 
		ret
endp skipToNextWord  

proc findLastWordBegining 
    lea si, bufer
    add si, maximalBuferSize
    
	mov buferPointer, maximalBuferSize       
	         
	mov cx, maximalBuferSize 
	inc cx  
	lastSymbolSearchLoop:
		dec si
		dec buferPointer 
		mov al, [si] 
		cmp al, 20h		;space
		je foundLastWord 
		cmp al, 09h		;tab  
		je foundLastWord
		cmp al, 0Dh 	;cret
		je foundLastWord 
		cmp al, 0Ah 	;newline
		je foundLastWord          
	loop lastSymbolSearchLoop
	
	foundLastWord:
	inc buferPointer 
	 
	ret
endp findLastWordBegining
	
proc operation  
	lea si, bufer
	mov buferPointer, 0    
	
	cmp inNewLineSearch, 1
	jne compareOperation  
	
	call skipToNewLine  
	
	cmp lastSymbol, 1
		je operationReturn  
	
	;if  still in search for new line
	
	compareOperation: 
	
	call compareWords
	
	cmp foundWord, 1
		je foundWordAction
	cmp lastSymbol, 1
		je operationReturn 
		
	call skipToNextWord
	 
	cmp lastSymbol, 1
		je operationReturn  
		
	jmp compareOperation
		
	foundWordAction:
	mov foundWord, 0
	
	additionalCheck:  
	cmp lastOperation, 1
	jne mainChecks
	
		mov ax, buferPointer
		cmp ax, currentBuferSize
		je reallyFoundWord 
	
	mainChecks:
	cmp [si], 20h	;space
	je reallyFoundWord
	cmp [si], 0Ah	;new line
	je reallyFoundWord 
	cmp [si], 0Dh   ;cret
	je reallyFoundWord   
	cmp [si], 09h   ;tab
	je reallyFoundWord  
	cmp [si], 2Eh  	;dot
	je reallyFoundWord 
	cmp [si], 2Ch   ;comma
	je reallyFoundWord 
	cmp [si], 21h   ;exclamation mark
	je reallyFoundWord 
	
	jmp notRealltFoundWord
	
	reallyFoundWord:
		dec lines
	     
	mov inNewLineSearch, 1
	call skipToNewLine       
	
	cmp lastSymbol, 1
		je operationReturn  
		
	jmp compareOperation 
	     
	notRealltFoundWord:
		mov ax, buferPointer
		cmp ax, currentBuferSize   
			je operationReturn
		
		call skipToNextWord
		cmp lastSymbol, 1
			je operationReturn 	
		
	jmp compareOperation 
	
    operationReturn:
    	mov lastSymbol, 0 
		ret
endp operation       

proc showResults
     readStringFrom linesString
     
    integerNumberToString:
    	mov ax, lines                
		mov bx, 10          ;divide by 10
		mov dx, 0           
		mov cx, 5			;maximal number of digits in number   
		
		lea si, numberString
		add si, 4	  
	                   
	integerNumberToStringLoop: 	
		div bx				
		mov [si], dl
		mov dx, 0
		add [si], '0'
		dec si
	loop integerNumberToStringLoop
    
    mov al, '0'
    mov cx, 5 
    lea si, numberString
	mov di, si
	
	toStringLoop:
	
		cmp [si], '0' 
		jne exitToStringLoop
		inc si    	
	loop toStringLoop  
	
	cmp cx, 0
	je zeroString
	
	exitToStringLoop:
	 	inc cx
		repe movsb	 
		jmp printInteger
	
	zeroString:
		inc di
		mov [di], '$' 
		
	printInteger:
		readStringFrom numberString
    	call exitProgram
   		ret
endp showResults   
	              
start:     
	call getInfoFromComandLine
    call initDataAndExtendedSegments 
    call openFile
    call readFile
    
    cmp lastOperation, 1
    je lo    
    
    mainLoop: 
   		call operation
		call loadNextSymbols
    	cmp lastOperation, 1 
   		jne mainLoop
   	
   	lo:
   		call operation	     
		call showResults		 
end start


