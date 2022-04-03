.model tiny 
org 100h 

.data
pointerCOM1 dw ?
inputString db "Enter symbol: ", 0Ah, 0Dh, '$'     
errorMessage db 0Ah, 0Dh, "Error occupied while sending", '$'
succeessSend db 0Ah, 0Dh, "Sending completed successfully", '$'   

.code
getChar macro
    mov ah, 01h			;writing char into al
    int 21h
endm 

readStringFrom macro pointer 
    mov ah, 09h  
    mov dx, offset pointer
    int 21h
endm      

main:
mov ax, 40h				;read address of standart input device (COM1 by default)   
mov es, ax   
mov dx, es:[00]  
mov pointerCOM1, dx 
                    	;setup
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
test al, 40h
jz wait 

sub dx, 5 
mov al, ah
out dx, al 

readStringFrom inputString
getChar
mov dx, pointerCOM1
add dx, 5  
out dx, al 
in al, dx   	;sending char
test al, 80h
jz succeess      

readStringFrom errorMessage
ret  

succeess:  
readStringFrom succeessSend
ret
 
end main