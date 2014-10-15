[bits 32]
[extern main] ; Define calling point. Must haveSame name as kernel.c 'main' function
call main ; Calls the C function. The linker will know where it is placed in memory
jmp $
