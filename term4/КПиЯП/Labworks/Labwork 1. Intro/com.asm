.model tiny          
              ;works
.code    
org 100h
         
         
macro carriageReturn 
    mov ah, 02h
     
    mov dl, 0Ah  
    int 21h  
    
    mov dl, 0Dh
    int 21h  
endm        
         
macro readStringFrom pointer
    mov ah, 09h  
    lea dx, pointer 
    int 21h
endm          
         
         
start:
    readStringFrom message
    carriageReturn
               
ret
          
message db "Hello world!", '$'                               
end start    