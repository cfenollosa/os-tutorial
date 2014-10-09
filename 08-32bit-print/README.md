*Concepts you may want to Google beforehand: 32-bit protected mode, VGA, video 
memory*

**Goal: Print on the screen when on 32-bit protected mode**

32-bit mode allows us to use 32 bit registers and memory addressing, 
protected memory, virtual memory and other advantages, but we will lose
BIOS interrupts and we'll need to code the GDT (more on this later)

In this lesson we will write a new print string routine which works in
32-bit mode, where we don't have BIOS interrupts, by directly manipulating
the VGA video memory instead of calling `int 0x10`. The VGA memory starts
at address `0xb8000` and it has a text mode which is useful to avoid
manipulating direct pixels.


The formula for accessing a specific character on the 80x25 grid is:

`0xb8000 + 2 * (row * 80 + col)`

That is, every character uses 2 bytes (one for the ASCII, another for 
color and such), and we see that the structure of the memory concatenates
rows.

Open `32bit-print.asm` to see the code. It will always print the string
on the top left of the screen, but soon we'll write higher level routines
to replace it.

Unfortunately we cannot yet call this routine from the bootloader, because
we still don't know how to write the GDT and enter protected mode. Once
you have understood the code, jump to the next lesson.
