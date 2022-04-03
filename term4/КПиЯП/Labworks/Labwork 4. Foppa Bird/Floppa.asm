
.model small
.stack 100h
.data 

;screen      
screenWidth equ 80
screenHeight equ 25                      

numberOfSkyRows equ 15 
numberOfDirtRows equ 10   

lose db 0
youLoose db "You were defeated! Press any key to continue. Press Q to exit."
                      
birdColumn equ 10                      
birdRaw db 13
birdRising db 0 





;physics
animationStep db 0 
animationSpeed db 0
animationCounter db 0

animationSpeedPointer dw 0
fallAnimationSpeeds db 5, 4, 4, 3, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0
riseAnimationSpeeds db 1, 2, 3, 4, 5, 0  
 
;score
score db 0
scoreLenght equ 3
scoreString scoreLenght + 1 dup ('$')    
scoreColor db 01110000b

;colors 
skyColor equ 00110000b
pipeColor equ 01100000b 
groundColor equ 00100000b   
birdColor equ 01011101b  


;frame
currentPageToShow db 0
currentPageToDraw db 0



;pipe  
numberOfPipes equ 2                      
spaceBetweenPipes equ 5

minimalHeight equ 3  
maximalHeight equ 17 

pipeHeights db  3, 9, 6, 19
pipeColoums db numberOfPipes dup (0)

currentPipeHeight db 0
currentPipeColumn db 0 
currentPipetoDraw db 0      



.code 
;cursor   
macro moveCursorTo raw, column, page	;uses ah, bh, dx
	mov ah, 02h
	mov bh, page
	mov dh, raw
	mov dl, column 
	int 10h	
endm
                            
proc getCursor	;uses ah, bh
	mov ah, 03h 
	mov bh, 00h
	int 10h 
	ret
endp getCursor 
   	

;logic
proc addNewPipe 
	push ax  
	
	call getRandomNumber
	mov [si], ah 			;currentPipeHeight
	mov [di], screenWidth	;currentPipeColumn
	
	pop ax    
	ret
endp addNewPipe    



proc getRandomNumber ;result in ah  
	push cx
	mov ah, 0
	int 1Ah 
	
	mov dh, 0
	mov ax, dx
	mov dl, maximalHeight
	sub dl, minimalHeight
	div dl
	add ah, minimalHeight 
	pop cx
	ret
endp getRandomNumber       

proc checkScore
	cmp [di], birdColumn 
	jne checkScoreDone 
	
	inc score
	
	checkScoreDone:  
	ret
endp checkScore
  
proc checkUppperBound	
	cmp birdRaw, 0 
	jne	didntTouchUpperBound  
	
	touchUpperBound:
	mov lose, 1 
	ret
	didntTouchUpperBound: 
	ret
endp    

proc checkLowerBound	
	cmp birdRaw, screenHeight - 1  
	jne	didntTouchLowerBound  
	
	touchLowerBound:
	mov lose, 1 
	ret
	didntTouchLowerBound: 
	ret
endp

proc checkPipe—ollision
	cmp currentPipeColumn, birdColumn
	je checkBirdRaw    
	mov al, currentPipeColumn 
	inc al
	cmp al, birdColumn 
	je checkBirdRaw  
	jmp checkPipe—ollisionReturn
	checkBirdRaw:
	
		mov al, currentPipeHeight 
		mov ah, al
		add ah, spaceBetweenPipes 
		inc al
		
		mov dl, birdRaw  
		
		cmp dl, al
		jb collisionLose 
		
		cmp dl, ah
		jg collisionLose 
	
	jmp checkPipe—ollisionReturn
	collisionLose: 
	mov lose, 1    
	    
	checkPipe—ollisionReturn:
	ret
endp checkPipe—ollision

;change pages procs
proc changePageToShow uses ax
	inc currentPageToShow
	
	cmp currentPageToShow, 4
	jne pageToShowOkey  
	
	
	pageToShowOverflow:
	mov currentPageToShow, 0
	
	pageToShowOkey:	 
	
	mov ah, 05
	mov al, currentPageToShow
	int 10h
	
	ret	
changePageToShow endp

proc changePageToDraw uses ax
	mov ah, 05
	mov al, currentPageToDraw
	int 10h
	
	inc currentPageToDraw
	cmp currentPageToDraw, 4
	jne pageToDrawOkey  
	
		mov currentPageToDraw, 0
	
	pageToDrawOkey:	 
	ret	
changePageToDraw endp  



;init
proc initPipeColumns uses ax, bx, cx 
	lea di, pipeColoums
	add di, numberOfPipes
	dec di 
	
	mov ax, screenWidth
	mov bh, 0
	mov bl, numberOfPipes  
	div bl             		
	
	mov cl, al 		;space between pipes
	
	mov ah, 0
	mov bl, 2
	div bl         	;half space
	
	mov bl, screenWidth
	sub bl, al 

	mov bh, cl		;space between pipes
	
	
	mov cx, numberOfPipes
	initPipeColumnsLoop:
		mov [di], bl
		sub bl, bh  
		dec di
	loop initPipeColumnsLoop 
	ret
endp initPipeColumns   

proc initPipeHeights
	mov cx, numberOfPipes
	lea di, pipeHeights
	add di, cx
	dec di 
	
	initPipeHeightsLoop:
		;call getRandomNumber
		mov [di], 11
		dec di
	loop initPipeHeightsLoop
	
	ret
endp initPipeHeights



;draw simple things              
macro drawSymbol color, symbolsNumber, page 
	mov cx,	symbolsNumber	;number of symbols to draw
	       
	mov ah, 09h 			;draw symbol
	mov bh, page 			;page (0-3) 
	
	mov al, ' '    			;symbol
	mov bl, color             
	
		
	int 10h	
endm
             
macro drawRaws color, rowsNumber, page 
	mov bl, screenWidth
	inc bl
	mov ax, rowsNumber
	mul bl				;number of symbols in many raws
	
	dec ax   
	
	mov bl, color 
	
	drawSymbol bl, ax, page
endm     



;draw complicated things 
proc drawBackground  uses ax, bx, cx 
	moveCursorTo 0, 0, currentPageToDraw   
	drawRaws skyColor, numberOfSkyRows, currentPageToDraw
	call getCursor 
	moveCursorTo numberOfSkyRows, 0, currentPageToDraw  
	call getCursor
    drawRaws groundColor, numberOfDirtRows, currentPageToDraw
	ret		
drawBackground endp 

proc drawPipe uses ax, bx, cx, dx  
	push cx 
	mov cx, 0 			;number of symbols before skip
	
	
	mov ax, 2            
    cmp currentPipeColumn, 79
    jne drawPipeLoop
    rightesColumn:         
    mov ax, 1	
    
    
    drawPipeLoop:    
    push cx 			;sholud save cl as couter 
    push ax               
	moveCursorTo cl, currentPipeColumn, currentPageToDraw
	pop ax
	push ax 
	drawSymbol pipeColor , ax, currentPageToDraw   
	pop ax
	pop cx
	
	cmp cl, currentPipeHeight		;skip place            
	jne skipAddPipeSpace   
    
    addPipeSpace: 
    	add cl, spaceBetweenPipes	;add space between pipes  
	skipAddPipeSpace:
		inc cl 
		cmp cl, screenHeight 
		jne drawPipeLoop 
		
	endDrawPipe:  
	pop cx     
	call checkScore
	ret
endp drawPipe
                       
proc drawPipes uses ax, bx, cx, dx
	mov cx, 0  		;currentPipeToDraw
	lea si, pipeHeights
	lea di, pipeColoums
	
	drawPipesLoop:
		mov al, [si]    
		mov currentPipeHeight, al 
		mov al, [di]   
		mov currentPipeColumn, al
		call drawPipe
		call checkPipe—ollision 
		
		cmp currentPipeColumn, 0
		jne pipeNotOnScreenEdge    
		
		pipeOnScreenEdge: 
			call addNewPipe  
		pipeNotOnScreenEdge:
		dec [di]
		
		inc si
		inc di
		
		inc cx
	
	cmp cl,	numberOfPipes
	jne drawPipesLoop
	ret	
endp drawPipes

proc drawScore 
	mov ax, 0ffeeh
	  
	integerNumberToString:  
	    mov di, offset scoreString	                  
		add di, scoreLenght			
		mov [di], '$'
		dec di				;to lowest digit
		mov bh, 0
		mov bl, 10          ;divide by 10        
		mov cx, scoreLenght	;maximal number of digits in number 
		
		mov ah, 0
		mov al, score
	                   
	scoreNumberToStringLoop: 
		mov ah, 0 	
		div bl				
		mov [di], ah
		mov dx, 0
		add [di], '0'
		dec di
	loop scoreNumberToStringLoop
	    
	drawSymbolString:
		mov cx, scoreLenght 
		mov dl, screenWidth
		sub dl, scoreLenght
		mov si, offset scoreString 
		
		drawSymbolLoop: 
			moveCursorTo 0, dl, currentPageToDraw
			inc dl 
			
			push cx
			mov cx,	1		;number of symbols to draw
			
			lodsb  
			mov bl, scoreColor             
			mov bh, currentPageToDraw 	;page (0-3) 
			
			
			mov ah, 09h 				;draw symbol	
			int 10h	
			pop cx   
		loop drawSymbolLoop
	
	ret
endp drawScore   

proc fallAnimation   
	cmp animationSpeedPointer, 0
	je setAnimationSpeedPointer
	
	cmp [animationSpeedPointer], 0
	jne checkFallAnimationCounter
	
	setAnimationSpeedPointer:
	mov ax, offset fallAnimationSpeeds  
	mov animationSpeedPointer, ax   
	 
	checkFallAnimationCounter: 
	cmp animationCounter, 0 
	jne fallAnimationContinue
	
	setFallAnimationCounter:
	mov si, animationSpeedPointer
	mov ax, [si]
	mov animationCounter, al	
	inc animationSpeedPointer 
	     
	fallAnimationContinue: 
		dec animationCounter
		cmp animationCounter, 0
		jne fallAnimationReturn
	
	fallAnimationOneDown: 
		call checkLowerBound
		cmp lose, 1
		je fallAnimationReturn
		inc birdRaw
	
	fallAnimationReturn:
	ret
endp fallAnimation
           
           
proc riseAnimation   
	cmp animationSpeedPointer, 0
	je setAnimationRiseSpeedPointer
	
	cmp [animationSpeedPointer], 0
	jne checkRiseAnimationCounter
	
	setAnimationRiseSpeedPointer:
	mov ax, offset riseAnimationSpeeds  
	mov animationSpeedPointer, ax   
	 
	checkRiseAnimationCounter: 
	cmp animationCounter, 0 
	jne riseAnimationContinue
	
	setRiseAnimationCounter:
	mov si, animationSpeedPointer
	mov ax, [si]
	mov animationCounter, al	
	inc animationSpeedPointer 
	     
	riseAnimationContinue: 
		dec animationCounter
		cmp animationCounter, 0
		jne riseAnimationReturn
	
	riseAnimationOneUp: 
	call checkUppperBound
	cmp lose, 1
	je riseAnimationReturn
	dec birdRaw
	
	riseAnimationReturn:
	ret
endp riseAnimation         
           
           
           
proc drawBird
	keyPressCheck: 
		mov ah, 01h
	    int 16h   
	    jnz keyPressed
    
    birdRisingCheck:
	    cmp birdRising, 1
	    jge rise
     
    fall:
		call fallAnimation   
		jmp endBirdDraw
	
	keyPressed:  
		mov animationSpeed, 0
		mov animationCounter, 0
		mov animationSpeedPointer, 0
		mov birdRising, 1
		
		mov ah, 08h  	;clean keyboard bufer
		int 21h
	
	rise:               
		call riseAnimation 
		cmp animationCounter, 0
		jne endBirdDraw
		mov si, animationSpeedPointer
		cmp [si], 0      
		jne endBirdDraw   
		
		mov birdRising, 0
	    mov animationSpeedPointer, 0
		
	endBirdDraw:
		moveCursorTo birdRaw, birdColumn, currentPageToDraw
		drawSymbol birdColor , 1, currentPageToDraw
		
	ret
endp drawBird



proc nextFrame
	call changePageToDraw    
	call drawBackground  
	call drawBird 
	call drawPipes
	
	cmp lose, 1
	je playerLose:
	
	call drawScore
	call changePageToShow
	jmp nextFrameReturn
	
	playerLose:
	dec score
	call drawScore
	call changePageToShow  
	
	jmp itsTimeToStop
	
	nextFrameReturn:
	ret	
endp nextFrame   
 


proc newGame  
	mov animationSpeedPointer, 0  
	mov animationSpeed, 0 
	mov animationCounter, 0
	mov birdRising, 0
	mov birdRaw, 13
	mov score, 0
	mov lose, 0
	call initPipeColumns  
    call initPipeHeights
	ret	
endp newGame  

proc gameplay     
   	nextFrameLoop:  
    call nextFrame   
    jmp nextFrameLoop 
	ret
endp   

proc drawLooseMessage
    ;mov ah, 13h
;    mov al, 00000000b
;    mov cx, 62
;    mov bl, birdColor
;    mov dh, 8
;    mov dl, 10
    
    mov si, offset youLoose
    
   ; int 10h    
    
    mov bl, currentPageToShow         
  	mov ax, 4096
  	mov bh, 0
  	mul bx
  	mov di, ax 
  	add di, 652h
  	                    
    mov ax, 0b800h
   	mov es, ax
   	
   	mov al, birdColor
   	mov cx, 62
   	
   	symbolLoop:
   		movsb 
   		stosb
   	loop symbolLoop 
   	
   	mov ax, @data
   	mov es, ax
   	
    
    waitForKey:
    mov ah, 00h
   	int 16h
   	
   	cmp al, 'q'
   	je exit      
    
    cmp al, 'Q'
   	je exit       
          
   call newGame 
    
    
	ret
endp drawLooseMessage
	
	
start:
   	mov ax, @data
   	mov ds, ax
   	mov es, ax			
    
   	mov ah, 0	     	;third video mode
   	mov al, 03h
   	int 10h     
   	
   	mov  ah, 1			;hide cursor
   	mov ch, 20h
   	int 10h   
    
    call newGame
    call gameplay

    
    itsTimeToStop:
    call drawLooseMessage
    call newGame
    call gameplay 
    
    exit: 
   	mov ah, 06h
   	mov al, 0h
   	mov ch, 0
   	mov cl, 0
   	mov bh, 00000111b
   	mov dh, screenHeight
   	dec dh
   	mov dl, screenWidth
  	dec dl
  	
  	int 10h 
    end:
   	mov ax, 4C00h
   	int 21h

end start