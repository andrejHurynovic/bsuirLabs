.model small    

.code 
.stack 100h

start: 
mov ah, 0          	;interruption number for port initialisation
mov al, 11100011b	;9600 bits per second (111), no partite check (00), stop bit length = 1 (1), number of bits in word = 8 (11)    
mov dx, 0          	;COM1 (0)  
int 14h

main:
mov ah, 2			;read symbol from port specified in DX 
int 14h            	
test ah, ah        	;if something received (ah != 0)
jnz nothingWasRecсived 

int 29h           	;print received symbol
 
nothingWasRecсived:
mov ah, 1 			    	
int 16h             
jz main             ;if nothing in stdin buffer 
mov ah, 8			
int 21h             ;write symbol from stdin to al without echo
test al, al         
jnz sendSymbol      ;if symbol was typed in
int 21h
cmp al, '-'         ;if '-' (close program)
jne sendSymbol  

mov ax, 4C00h 		
int 21h             ;return control to operating system

sendSymbol:
mov ah, 1          	 
int 14h             ;send symbol to port specified in DX
jmp main  
 
end start