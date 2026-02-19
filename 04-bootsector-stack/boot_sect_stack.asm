mov ah, 0x0e ; tty mode

mov bp, 0x8000 	; this is an address far away from 0x7c00 so that we don't get overwritten
mov sp, bp 	; if the stack is empty then sp points to bp
; if we push (0x8000 - 0x7c00) bits (0x400 or 1,024 bits), we will start to write over
; the bootloader. so, don't do that! 

; still in 16-bit mode, so these each push 16 bits onto the stack. 
push 'A'
push 'B'
push 'C'

; to show how the stack grows downwards
mov al, [0x7ffe] ; 0x8000 - 16 bits
int 0x10

mov al, [0x8000] ; this is a null byte - it's the top of the stack
int 0x10

mov al, [0x7ffa] ; 0x8000 - 48 bits. lower in memory
int 0x10


; recover our characters using the standard procedure: 'pop'
; We can only pop full words so we need an auxiliary register to manipulate
; the lower byte
pop bx
mov al, bl
int 0x10 ; prints C

pop bx
mov al, bl
int 0x10 ; prints B

pop bx
mov al, bl
int 0x10 ; prints A

; data that has been pop'd from the stack is garbage now
mov al, [0x8000]
int 0x10


jmp $
times 510-($-$$) db 0
dw 0xaa55
