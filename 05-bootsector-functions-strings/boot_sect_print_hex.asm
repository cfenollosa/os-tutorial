; receiving the data in 'dx'
; For the examples we'll assume that we're called with dx=0x1234
print_hex:
    pusha

    mov cx, 0 ; our index variable

loop:
    cmp cx, 4 ; loop 4 times
    je end
    
    mov ax, dx ; we will work on ax
    and ax, 0x000f ; 0x1234 -> 0x0004 by masking first three to zeros
    ; convert each hex value to its ASCII value. '0' (ASCII 0x30) to '9' (0x39) 
    ; We will need to convert byte N to byte 0x3N by just adding 0x30
    add ax, 0x30 ; 0x0004 -> ASCII '4'

    ; bx <- address of the character to replace = base + string length - index
    mov bx, HEX_OUT + 5 ; last char of string, beware not to replace null char
    sub bx, cx  ; address of char to replace
    or [bx], ax ; copy the ASCII char to the string position
    ror dx, 4 ; 0x1234 -> 0x4123 -> 0x3412 -> 0x2341 -> 0x1234

    ; increment index and loop
    add cx, 1
    jmp loop

end:
    ; prepare the parameter and call the function
    ; remember that print receives parameters in 'bx'
    mov bx, HEX_OUT
    call print

    popa
    ret

HEX_OUT:
    db '0x0000',0 ; reserve memory for our new string
