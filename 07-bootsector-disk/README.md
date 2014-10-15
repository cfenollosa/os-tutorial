*Concepts you may want to Google beforehand: hard disk, cylinder, head, sector, 
carry bit*

**Goal: Let the bootsector load data from disk in order to boot the kernel**

Our OS won't fit inside the bootsector 512 bytes, so we need to read data from
a disk in order to run the kernel.

Thankfully, we don't have to deal with turning spinning platters on and off,
we can just call some BIOS routines, like we did to print characters on the screen.
To do so, we set `al` to `0x02` (and other registers with the required cylinder, head
and sector) and raise `int 0x13`

You can access [a detailed int 13h guide here](http://stanislavs.org/helppc/int_13-2.html)

On this lesson we will use for the first time the *carry bit*, which is an extra bit
present on each register which stores when an operation has overflowed its current
capacity:

```nasm
mov ax, 0xFFFF
add ax, 1 ; ax = 0x0000 and carry = 1
```

The carry isn't accessed directly but used as a control structure by other operators,
like `jc` (jump if the carry bit is set)

The BIOS also sets `al` to the number of sectors read, so always compare it
to the expected number.


Code
----

Open and examine `boot_sect_disk.asm` for the complete routine that
reads from disk.

`boot_sect_main.asm` prepares the parameters for disk read and calls `disk_load`.
Notice how we write some extra data which does not actually belong to the boot
sector, since it is outside the 512 bits mark.

The boot sector is actually sector 1 (the first one, sectors start at 1)
of cylinder 0 of head 0 of hdd 0.

Thus, any bytes after byte 512 correspond to sector 2 of cylinder 0 of head 0 of hdd 0

The main routine will fill it with sample data and then let the bootsector
read it.

**Note: if you keep getting errors and your code seems fine, make sure that qemu
is booting from the right drive and set the drive on `dl` accordingly**

The BIOS sets `dl` to the drive number before calling the bootloader. However,
I found some problems with qemu when booting from the hdd.

There are two quick options:

1. Try the flag `-fda` for example, `qemu -fda boot_sect_main.bin` which will set `dl`
as `0x00`, it seems to work fine then.
2. Explicitly use the flag `-boot`, e.g. `qemu boot_sect_main.bin -boot c` which 
automatically sets `dl` as `0x80` and lets the bootloader read data


