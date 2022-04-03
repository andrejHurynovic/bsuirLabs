.model tiny
.code 
org 100h

start: 

call getInfoFromCL   

cmp execution, 0
jne ok

call exitProgram

ok:

resizeMemory:     
	mov bx, programLenght + 100h + 200h
	mov sp, bx  
	
	shr bx, 4
	inc bx
	mov ah, 4ah
	int 21h
        
	jc freeMemoryError
	jmp exec

freeMemoryError:
    mov errorNumber, 2
    call errorHandler

exec: 
    mov ax, cs
    mov word ptr EPB + 4, ax   
    mov word ptr EPB + 8, ax   
    mov word ptr EPB + 0Ch, ax
    
    mov cx, execution
    execLoop:
	    mov dx, offset filePath
	    mov bx, offset EPB
	    mov al, 0
	    mov ah, 4Bh
	    int 21h
	    
	    jc errorInExec   
	loop execLoop
    int 20h
    
    errorInExec:
    cmp ax, 02h
        je fileNotFound
    cmp ax, 05h
        je fileAccessDenied
    cmp ax, 08h
        je notEnoughtMemory
    cmp ax, 0Ah
        je incorrectEnviroment
    cmp ax, 0Bh
        je incrrrectFormat
    
    
    fileNotFound:
        mov errorNumber, 3
        call errorHandler
    fileAccessDenied:
        mov errorNumber, 4
        call errorHandler
    notEnoughtMemory:
        mov errorNumber, 5
        call errorHandler
    incorrectEnviroment:
        mov errorNumber, 6
        call errorHandler
    incrrrectFormat:
        mov errorNumber, 7
        call errorHandler
        
        int 20h


;data
filePath db "A:\test7.exe", 0

numberSize db 0
errorNumber db 0
execution dw 0
                       
;execute parameter block
EPB             dw 0                     ;current environment
                dw offset commandLine, 0 ;commandLineAddres
                dw 005Ch, 0, 006Ch, 0    ;two FCB addresses
    commandLine db 5
    cdf db " cool"
    commandLineText db 120 dup (?) 
    
programLenght equ $-start
                     
               
;errors
invalidParametersString     db "Invalid arguments!", '$'
graterThenMaximalNuberSting db "Out of bounds: [0, 255]", '$'
freeMemoryString            db "Error in free memory proc",'$'
fileNotFoundString          db "File not found",'$'
fileAccessDeniedString      db "File access denied",'$'
notEnoughtMemoryString      db "Not enought memory",'$'
incorrectEnviromentString   db "Invalid enviroment",'$'
incrrrectFormatString       db "Invalid format",'$'              


;procs
proc errorHandler
    
    cmp errorNumber, 0
    je invalidParameters

    cmp errorNumber, 1
    je graterThenMaximalNuberError:
    
    cmp errorNumber, 2
    je freeMemoryPoint
    
    cmp errorNumber, 3
    je fileNotFoundError
    
    cmp errorNumber, 4
    je fileAccessDeniedError
    
    cmp errorNumber, 5
    je notEnoughtMemoryError
    
    cmp errorNumber, 6
    je incorrectEnviromentError
    
    cmp errorNumber, 7
    je incrrrectFormatError
    
    invalidParameters:
    lea dx, invalidParametersString
    jmp printError
    
    graterThenMaximalNuberError:
    lea dx, graterThenMaximalNuberSting
    jmp printError
    
    freeMemoryPoint:
    lea dx, freeMemoryString
    jmp printError
    
    fileNotFoundError:
    lea dx, fileNotFoundString
    jmp printError
    
    fileAccessDeniedError:
    lea dx, fileAccessDeniedString
    jmp printError
    
    notEnoughtMemoryError:
    lea dx, notEnoughtMemoryString
    jmp printError
    
    incorrectEnviromentError:
    lea dx, incorrectEnviromentString
    jmp printError
    
    incrrrectFormatError:
    lea dx, incrrrectFormatString
    jmp printError
     
    printError:
        mov al, 00h
        mov ah, 09h
        int 21h
    
    call exitProgram
endp

proc getInfoFromCL
    
    mov ch, 0
    mov cl, [0080h]    ;CL size
    
    cmp cl, 1
    jbe noParamError
                      
    mov si, 81h            ;comand line text begining
    mov ax, 0            ;number
    getInfoLoop:
        spaceCheck:
            cmp [si], ' '
            je endGetInfoLoop
        
        digitsCheck:
            cmp [si], '0'
            jb noParamError
            
            cmp [si], '9'
            jg noParamError
            
        cmp es:numberSize, 3
        je graterThenMaximalNumber
           
        digitToNumber:
            mov bx, 10
            mul bx
            
            sub [si], '0'
            add al, [si]
            jc graterThenMaximalNumber
            inc numberSize
    endGetInfoLoop:
        inc si
    loop getInfoLoop
    
    cmp numberSize, 0
    je noParamError
    cmp numberSize, 3
    jg noParamError
    
    cmp ax, 100h
    jg graterThenMaximalNumber 
    
    mov execution, ax
    
    ret
    graterThenMaximalNumber:
        mov errorNumber, 1
        call errorHandler
    noParamError:
        mov errorNumber, 0
        call errorHandler
endp getInfoFromCL


proc exitProgram
    mov ah, 4ch
    mov al, 00h
    int 21h
    ret
endp exitProgram            
end start