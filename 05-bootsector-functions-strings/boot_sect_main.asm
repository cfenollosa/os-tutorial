[org 0x7c00] ; tell the assembler that our offset is bootsector code

; The main routine makes sure the parameters are ready and then calls the function
mov bx, HELLO
call print

; We will get fancy and print a newline
mov ah, 0x0e
mov al, 0x0A ; newline char
int 0x10
mov al, 0x0D ; carriage return char
int 0x10
; feel free to integrate this into "boot_sect_print" if you want to

mov bx, GOODBYE
call print

; that's it! we can hang now
jmp $

; remember to include subroutines below the hang
%include "boot_sect_print.asm"

; data
HELLO:
    db 'Hello, World', 0

GOODBYE:
    db 'Goodbye', 0

; padding and magic number
times 510-($-$$) db 0
dw 0xaa55
