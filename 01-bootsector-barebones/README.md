*Concepts you may want to Google beforehand: assembler, BIOS, UEFI, coreboot*

**Goal: Create a file which the BIOS interprets as a bootable disk**

This is very exciting, we're going to create our own boot sector!

Introduction
------------

After turning power on, boot firmware initializes hardware and run whatever
we want, usually an OS, but sometimes also some maintenance tools (memtest,
chipsec, firmware update etc.). Program which let us load any tool or an OS
at that point is called boot loader (eg. GRUB). For many years BIOS had been
a standard boot firmware in x86 platform, but since early 2010s UEFI has been
a new one.

UEFI brings a lot of new features. It runs in protected mode, it has FAT
filesystem support. It's also mostly written in C, so with it we can write a
bootloader in pure C. Unlike BIOS, it looks for a boot program on all recognized
filesystems. That's why boot loader must be adapted to one of them (or both).
QEMU's default is SeaBIOS, but on most of modern PCs (and mac)
UEFI is used. In this text we describe BIOS boot loading, so it won't work
on UEFI machine unless "Legacy BIOS mode" is on (usually it can be enabled in
configuration utility).

If you want to create a UEFI compatible bootloader, you should take a look at
https://github.com/tianocore/edk2 which is UEFI reference implementation. It's
also what you need to write an UEFI application. There is also OVMF package,
which allows to run UEFI on QEMU.

Be also aware that those are not only boot firmware widely used. In embedded, u-boot
is quite popular (eg. on Raspberry Pi). Another interesting boot firmware is coreboot
(https://www.coreboot.org/), which is open source and used (among others) in
ChromeBooks and Purism laptops. Coreboot can be compiled with BIOS and UEFI
interfaces as well, but often it's not necessery, because it can load GRUB, OS kernel
or custom aplication. The only limitation is that it must fit firmware memory
(usually ~8MB, so for generic Linux kernel it's nor enough. It can be compliled for QEMU
too.

Theory
------

When BIOS has initialized hardware it's ready to load a boot loader. BIOS can access
hard drives, optical media, USB sticks, but it has no file system drivers. Instead, it
looks for a valid boot sector in first 512 bytes of the disk (cylinder 0, head 0,
sector 0). If it ends with `0xAA55` (little endian), BIOS will run code found in boot
sector.

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
