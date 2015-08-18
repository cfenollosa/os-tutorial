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

We also delete the underscores around `__asm__` and `__volatile__` since they aren't needed.


4. Improperly aligned `kmalloc`
-------------------------------

First, since `kmalloc` uses a size parameter, we'll use the correct data type `size_t` instead
of `u32int_t`. `size_t` should be used for all parameters which "count" stuff and cannot be
negative. Include `<stddef.h>`. 

We will fix our `kmalloc` in the future, making it a proper memory manager and aligning data types.
For now, it will always return a new page-aligned memory block.


5. Missing functions
--------------------

We will implement the missing `mem*` functions in following lessons


6. Interrupt handlers
---------------------
`cli` is redundant, since we already established on the IDT entries if interrupts
are enabled within a handler using the `idt_gate_t` flags.

`sti` is also redundant, as `iret` loads the eflags value from the stack, which contains a 
bit telling whether interrupts are on or off.
In other words the interrupt handler automatically restores interrupts whether or not 
interrupts were enabled before this interrupt


On `cpu/isr.h`, `struct registers_t` has a couple issues. 
First, the alleged `esp` is renamed to `useless`.
The value is useless because it has to do with the current stack context, not what was interrupted.
Then, we rename `useresp` to `esp`

Finally, we add `cld` just before `call isr_handler` on `cpu/interrupt.asm`

