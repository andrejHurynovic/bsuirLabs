.model small
.stack 100h

.code          

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
    mov ax, @data
    mov ds, ax
    readStringFrom string 
    carriageReturn
    
    mov ax, 4C00h
    int 21h
 
.data 
string db "Hello world!!", '$'   
end start    
