*Concepts you may want to Google beforehand: C types and structs, include guards, type attributes: packed, extern, volatile, exceptions*

**Goal: Set up the Interrupt Descriptor Table to handle CPU interrupts**

This lesson and the following ones have been heavily inspired
by [JamesM's tutorial](https://web.archive.org/web/20160412174753/http://www.jamesmolloy.co.uk/tutorial_html/index.html)

Data types
----------

First, we will define some special data types in `cpu/types.h`,
which will help us uncouple data structures for raw bytes from chars and ints.
It has been carefully placed on the `cpu/` folder, where we will
put machine-dependent code from now on. Yes, the boot code
is specifically x86 and is still on `boot/`, but let's leave
that alone for now.

Some of the already existing files have been changed to use
the new `u8`, `u16` and `u32` data types.

From now on, our C header files will also have include guards.


Interrupts
----------

Interrupts are one of the main things that a kernel needs to 
handle. We will implement it now, as soon as possible, to be able
to receive keyboard input in future lessons.

Another examples of interrupts are: divisions by zero, out of bounds,
invalid opcodes, page faults, etc.

Interrupts are handled on a vector, with entries which are
similar to those of the GDT (lesson 9). However, instead of
programming the IDT in assembly, we'll do it in C.

`cpu/idt.h` defines how an idt entry is stored `idt_gate` (there need to be
256 of them, even if null, or the CPU may panic) and the actual
idt structure that the BIOS will load, `idt_register` which is 
just a memory address and a size, similar to the GDT register.

Finally, we define a couple variables to access those data structures
from assembler code.

`cpu/idt.c` just fills in every struct with a handler. 
As you can see, it is a matter
of setting the struct values and calling the `lidt` assembler command.


ISRs
----

The Interrupt Service Routines run every time the CPU detects an 
interrupt, which is usually fatal. 

We will write just enough code to handle them, print an error message,
and halt the CPU.

On `cpu/isr.h` we define 32 of them, manually. They are declared as
`extern` because they will be implemented in assembler, in `cpu/interrupt.asm`

Before jumping to the assembler code, check out `cpu/isr.c`. As you can see,
we define a function to install all isrs at once and load the IDT, a list of error
messages, and the high level handler, which kprints some information. You
can customize `isr_handler` to print/do whatever you want.

Now to the low level which glues every `idt_gate` with its low-level and
high-level handler. Open `cpu/interrupt.asm`. Here we define a common
low level ISR code, which basically saves/restores the state and calls
the C code, and then the actual ISR assembler functions which are referenced
on `cpu/isr.h`

Note how the `registers_t` struct is a representation of all the registers
we pushed in `interrupt.asm`

That's basically it. Now we need to reference `cpu/interrupt.asm` from our
Makefile, and make the kernel install the ISRs and launch one of them.
Notice how the CPU doesn't halt even though it would be good practice
to do it after some interrupts.
