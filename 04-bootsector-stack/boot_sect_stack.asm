mov ah, 0x0e ; tty mode

mov bp, 0x8000 ; this is an address far away from 0x7c00 so that we don't get overwritten
mov sp, bp ; if the stack is empty then sp points to bp

push 'A'
push 'B'
push 'C'

; to show how the stack grows downwards
mov al, [0x7ffe] ; 0x8000 - 2
int 0x10 ; prints A

mov al, [0x7ffc] ; 0x8000 - 4
int 0x10 ; prints B

mov al, [0x7ffa] ; 0x8000 - 6
int 0x10 ; prints C

; however, don't try to access [0x8000] now, because it won't work
; 0x8000 is just the base address and doesn't contain anything
mov al, [0x8000]
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


jmp $
times 510-($-$$) db 0
dw 0xaa55
