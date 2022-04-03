.model small
.stack 100h
  
 
.data
maximalStringSize equ 200  
stringPointer db maximalStringSize     
stringSize db 0
string db maximalStringSize dup (?)    

searchStringPointer db maximalStringSize     
searchStringSize db 0
searchString db maximalStringSize dup (?)   

infoString1 db "Enter main string:$"
infoString2 db "Enter search string$" 


.code                      
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


                     
macro carriageReturn 
    mov ah, 02h
     
    mov dl, 0Ah  
    int 21h  
    
    mov dl, 0Dh
    int 21h  
endm

    
      
start:
    mov ax, @data                      
    mov ds, ax
    mov es, ax 
    
    readStringFrom infoString1
    carriageReturn   
    writeStringTo stringPointer    
    carriageReturn
    
secondStringEnter:
    readStringFrom infoString2
    carriageReturn 
    writeStringTo searchStringPointer       
    carriageReturn 
    
    
    mov al, searchStringSize
    cmp al, stringSize 
    ja secondStringEnter    
    
secondStringSpacesCheck:
    lea di, searchString
    
    mov ch, 0
    mov cl, searchStringSize
    inc cx
    
    mov ah, 0
    mov al, ' '  
    
    cld 
    repnz scasb
    cmp cx, 0
    jne secondStringEnter 
    
    
            
    lea si, string
       
compareWords:
    cmp [si], '$'
    je printString 
           
    lea di, searchString       
    mov ch, 0
    mov cl, searchStringSize
    
    cld     
    repe cmpsb  
          
    jne notThisWord
    
    jmp foundWord 
    
notThisWord:
    dec si
    jmp wordSearch    
    
wordSearch: 
    cmp [si], '$'
    je printString
  
    mov al, [si]   
    inc si                       
    cmp al, ' '  
    ;
    je compareWords
    jmp wordSearch   
   
foundWord:    
    cmp [si], '$'
    je printString
    
    cmp [si], ' '
    jne wordSearch  
    
deleteWord:
    inc si
    mov di, si  
    
spacesCheck:                     
    cmp [si], ' '
    je foundSpace
    
    cmp [si], '$'
    je printString
     
    mov cx, 0
    jmp countWordSize

foundSpace:   
    inc si  
    jmp spacesCheck    
     
countWordSize:
    cmp [si], ' '
    je replaceWord  
    
    cmp [si], '$'
    je endFoundInWordSizeSearch  
    
    jmp wordEndNotFound
        
wordEndNotFound:  
    inc si
    inc cx
    jmp countWordSize     
        
replaceWord:
    mov di, si
    sub di, cx
    mov dx, di 
    
moveWord:
    movsb
    cmp [si], '$'
    jne moveWord
    jmp endFound
    
endFound:
    mov [di], '$'
    mov si, dx
    jmp wordSearch
    

endFoundInWordSizeSearch:
   sub si, cx
   mov [si], '$' 
    
printString:        
   readStringFrom string
   
   mov ax, 4C00h
   int 21h                      
                        
end start      