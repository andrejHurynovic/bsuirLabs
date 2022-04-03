.model tiny   
org 100h 
 
.data
pointerCOM1 dw ?
input_ok db "Reciving completed successfully", 0Ah, 0Dh, '$'    
errorMessage db "Error occupied while reciving", '$'    

.code
putChar macro symbol
    mov ah, 06h
    mov dl, symbol
    int 21h
endm 

readStringFrom macro pointer 
    mov ah, 09h  
    mov dx, offset pointer
    int 21h
endm      

main:
mov ax, 40h       	;read address of standart input device (COM1 by default)
mov es, ax   
mov dx, es:[02]
mov pointerCOM1, dx  

add dx, 3
mov al, 80h
out dx, al   

sub dx, 2  
mov al, 0
out dx, al 

dec dx 
mov al, 18h 
out dx, al 

add dx, 3
mov al, 00011011b  
out dx, al  

dec dx
dec dx
mov al, 00h  
out dx, al  

mov dx, pointerCOM1
add dx, 5

wait:
in al, dx
test al, 01h
jz wait   

sub dx, 5   
in al, dx
push ax 
add dx, 5
in al, dx
test al, 80h
jz ok
readStringFrom errorMessage
ret

ok: 
readStringFrom input_ok
    pop ax
    putChar al
    ret
    
end main  


