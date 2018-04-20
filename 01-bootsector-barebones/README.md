*Concepts you may want to Google beforehand: assembler, BIOS*

**Goal: Create a file which the BIOS interprets as a bootable disk**

This is very exciting, we're going to create our own boot sector!

Theory
------

When the computer boots, the BIOS doesn't know how to load the OS, so it
delegates that task to the boot sector. Thus, the boot sector must be
placed in a known, standard location. That location is the first sector
of the disk (cylinder 0, head 0, sector 0) and it takes 512 bytes.

To make sure that the "disk is bootable", the BIOS checks that bytes
511 and 512 of the alleged boot sector are bytes `0xAA55`.

This is the simplest boot sector ever:

```
e9 fd ff 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
[ 29 more lines with sixteen zero-bytes each ]
00 00 00 00 00 00 00 00 00 00 00 00 00 00 55 aa
```

It is basically all zeros, ending with the 16-bit value
`0xAA55` (beware of endianness, x86 is little-endian). 
The first three bytes perform an infinite jump

Simplest boot sector ever
-------------------------

You can either write the above 512 bytes
with a binary editor, or just write a very
simple assembler code:

```nasm
; Infinite loop (e9 fd ff)
loop:
    jmp loop 

; Fill with 510 zeros minus the size of the previous code
times 510-($-$$) db 0
; Magic number
dw 0xaa55 
```

To compile:
`nasm -f bin boot_sect_simple.asm -o boot_sect_simple.bin`

> OSX warning: if this drops an error, read chapter 00 again

I know you're anxious to try it out (I am!), so let's do it:

`qemu boot_sect_simple.bin`

> On some systems, you may have to run `qemu-system-x86_64 boot_sect_simple.bin` If this gives an SDL error, try passing the --nographic and/or --curses flag(s).

You will see a window open which says "Booting from Hard Disk..." and
nothing else. When was the last time you were so excited to see an infinite
loop? ;-)
