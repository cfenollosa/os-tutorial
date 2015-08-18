*Concepts you may want to Google beforehand: XX*

**Goal: Fix miscellaneous issues with our code**

The OSDev wiki has a section [which describes some issues with
JamesM's tutorial](http://wiki.osdev.org/James_Molloy%27s_Tutorial_Known_Bugs).
Since we followed his tutorial for lessons 18-22 (interrupts through malloc), we'll
need to make sure we fix any of the issues before moving on.

1. Wrong CFLAGS
---------------

We add  `-ffreestanding` when compiling `.o` files, which includes `kernel_entry.o` and thus
`kernel.bin` and `os-image.bin`.

Before, we disabled libgcc (not libc) through the use of `-nostdlib` and we didn't re-enable
it for linking. Since this is tricky, we'll delete `-nostdlib`

`-nostdinc` was also pased to gcc, but we will need it for step 3.

2. kernel.c `main()` function
-----------------------------

Modify `kernel/kernel.c` and change `main()` to `kernel_main()` since gcc recognizes "main" as 
a special keyword and we don't want to mess with that.

Change `boot/kernel_entry.asm` to point to the new name accordingly.

To fix the `i386-elf-ld: warning: cannot find entry symbol _start; defaulting to 0000000000001000`
warning message, add a `global _start;` and define the `_start:` label in `boot/kernel_entry.asm`.


3. Reinvented datatypes
-----------------------

It looks like it was a bad idea to define non-standard data types like `u32` and such, since
C99 introduces standard fixed-width data types like `uint32_t`

We need to include `<stdint.h>` which works even in `-ffreestanding` (but requires stdlibs)
and use those data types instead of our own, then delete them on `type.h`

<stddef.h> to provide size\_t



5. Missing functions
--------------------

6. Interrupt handlers
---------------------
- also cli, sti in interrupt handlers


7. Structs and attributes
-------------------------

8. Improperly aligned `kmalloc`
-------------------------------


