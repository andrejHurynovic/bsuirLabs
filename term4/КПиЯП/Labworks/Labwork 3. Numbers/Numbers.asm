.model small
.stack 130h
  
 
.data 
maximalNumberOfElements equ 30
numberOfEnteredNumbers db 0

 
stringPointer db 7		;7 = 1 – sign, 5 – digits, 1 – '$' 
stringSize db 0
string db 7 dup (?)

negativeFlag db ?		;check for '-' in string 

tempDoubleWord dd 0
tempAverage dd 0 
average dd 0 

enterString db "Enter number in range [-32768, 32767], enter 'S' to stop.", 0Dh, 0Ah, '$'
enterNumberString db "Enter number: ", '$' 
outOfRangeString db "Out of range!", 0Dh, 0Ah, '$'
notDigitString db "Incorrect symbol detected!", 0Dh, 0Ah, '$'
resultString db "Incorrect symbol detected!", 0Dh, 0Ah, '$'	 
 
 
macro writeStringTo pointer 
    lea dx, pointer 
    
    mov bx, dx                                                                                                
    
    mov ax, 0A00h                  
    int 21h                                        
    
    mov al, [bx + 1]   
    mov ah, 0
    
    add bx, ax 
    mov [bx + 2], '$' 
endm     
                                              
macro readStringFrom pointer
    mov ax, 0900h  
    lea dx, pointer 

    int 21h
endm  

macro printChar char  
	mov dl, char  
	
	mov ah, 02h
    int 21h   
endm          


macro addNumber
	mov ax, word ptr average            ;mov tempAverage, average
	mov word ptr tempAverage, ax   
	mov ax, word ptr [average + 2]
	mov word ptr [tempAverage + 2], ax 

	lea bx, tempDoubleWord     			;average = tempAverage + tempDoubleWord 
	mov ax, [bx]                	
	add ax, [bx + 4]
	mov [bx + 8], ax
	mov ax, [bx + 2]
	adc ax, [bx + 6]
	mov [bx + 10], ax
endm     
 

.code  

carriageReturn proc uses ah, dl
	mov ah, 02h
     
    mov dl, 0Ah  
    int 21h  
    
    mov dl, 0Dh
    int 21h  
  
	ret
endp 


start:
mov ax, @data
mov ds, ax  
mov es, ax

readStringFrom enterString
 
enterNumber:
	mov cx, 0
	
 	cmp numberOfEnteredNumbers, maximalNumberOfElements		;if maximal number of elements reached 
    je suming
    
	readStringFrom enterNumberString
	writeStringTo stringPointer
	call carriageReturn

checkNumber:
	cmp string, 'S'			;stop enter 
    je suming           	
    
    cmp string, '-'
    je  negativeNumber 
    
	positiveNumber:
		cmp stringSize, 6 	;if positive number if bigger then 5 symbols
		je outOfRange
		
		lea si, string
		mov negativeFlag, 0
   		jmp checkDigits
    
	negativeNumber: 
		lea si, string + 1
		mov negativeFlag, 1


	checkDigits:
		cmp [si], '$'		;if end of number
		je stoi
	
		cmp [si], '0'
		jl notDigit
	
		cmp [si], '9'
		ja notDigit
	
		inc cx
		inc si
		jmp checkDigits


	
stoi:
	sub si, cx
	mov ax, 0
	mov bh, 0
	
	stoiLoop: 
		mov dx, 10
		mul dx
		jc outOfRange 
		sub [si], '0' 
		mov bl, [si]
		add ax, bx
		jc outOfRange
		inc si	
	loop stoiLoop



checkRange:
	cmp negativeFlag, 1
	je checkNegative	

	checkPositive: 	
		cmp ax, 32767
		ja outOfRange
		jmp addToStack
	
	checkNegative: 	
		cmp ax, 32768
		ja outOfRange
		neg ax
	
	addToStack:
		inc numberOfEnteredNumbers 
		push ax 
		jmp enterNumber
	


errors:
	notDigit:
		readStringFrom notDigitString
		jmp enterNumber

	outOfRange:
		readStringFrom outOfRangeString
		jmp enterNumber
 
 


suming:
	cmp numberOfEnteredNumbers, 0
	je printZeroEnd   
	
	mov ch, 0
	mov cl, numberOfEnteredNumbers

	sumingLoop:
		pop word ptr tempDoubleWord		
		cmp word ptr tempDoubleWord, 0
		jns positive
	
		negative:
		mov word ptr [tempDoubleWord + 2], 1111111111111111b	;make second word negative 0, FFFFh does't works
		addNumber
		jmp next
	
		positive: 
		mov word ptr [tempDoubleWord + 2], 0000h
		addNumber

		next:	
	loop sumingLoop



dividing:  
	cmp average, 0
	je printZeroEnd


	mov ax, average  	
	mov dx, [average + 2]
	mov ch, 0
	mov cl, numberOfEnteredNumbers
	idiv cx				;integer in ax, fractional in dx 
    
    mov word ptr average, dx
 
 
prepareString:
	lea si, string
	
	cmp ax, 0
	js addMinus

	addPlus:
	mov [si], '0'         
	
	cmp ax, 0
	je printIntegerZero 
	
	jmp integerNumberToString 
	
	addMinus:  
	mov [si], '-'  
	
	cmp ax, 0
	je printIntegerZero  
	
	neg ax 
                 
 
	 
integerNumberToString:	                  
	add si, 6			
	mov [si], '$'
	dec si				;to lowest digit
	mov bx, 10          ;divide by 10
	mov dx, 0           
	mov cx, 5			;maximal number of digits in number 
	                   
	integerNumberToStringLoop: 	
		div bx				
		mov [si], dl
		mov dx, 0
		add [si], '0'
		dec si
		
	loop integerNumberToStringLoop	 
	
convertStringToNormalString:  
	lea si, string
	lea di, string 
	
	mov cx, 6    
	
	cmp [si], '-'
	jne convertloop
  
	    inc si
	    inc di
	    dec cx
	  
		convertloop:
		cmp [si], '0'
		jne deleteZeroes  
	
		inc si 
	
		loop convertloop  
	
	deleteZeroes:
		inc cx
		
		repe movsb 
		
printInteger:
	readStringFrom string
	jmp checkFractional  

printIntegerZero:
	cmp [si], '-'
	jne printPositiveIntegerZero 
	inc si
	mov [si], '0'
		printPositiveIntegerZero:
		inc si
		mov [si], '$'
	
	readStringFrom string	

	
checkFractional: 	
	cmp average, 0 
	jne convertFractional
	jmp end 
    
    convertFractional:
	    printChar ','   
	    
	    mov ax, word ptr average
	    mov cx, 3
	    lea si, string      
	    
	    cmp ax, 0
	    jns convertFractionalLoop
	    
	    negativeFractional:
	    	neg ax	 
	    
	    convertFractionalLoop:
		    mov dl, 10
		    mul dl
		    mov dl, numberOfEnteredNumbers
		    div dl
		    
		    mov [si], al
		    add [si], '0'
		    inc si   
		    
		    cmp ah, 0
		    je printFractional
		    
		    mov al, ah
		    mov ah, 0	 	
		     	
	    loop convertFractionalLoop
    
printFractional:
	 mov [si], '$'
	 readStringFrom string    
	 jmp end
    
    
    
    
    
    
printZeroEnd:
    printChar '0'  

    
				
end:   
   	mov ax, 4C00h
  	int 21h                      
                        
end start      
