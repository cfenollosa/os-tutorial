; A simple boot sector program that loops forever

mov ah,oeh
mov si,msg

printing
mov al,[si]
add si,1
or al,0
je exit
jmp printing
exit:






msg  db "hello world",0
times 510-($-$$) db 0
dw 0xaa55
