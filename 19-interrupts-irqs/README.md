*Concepts you may want to Google beforehand: IRQs, PIC, polling*

**Goal: Finish the interrupts implementation and CPU timer**

When the CPU boots, the PIC maps IRQs 0-7 to INT 0x8-0xF
and IRQs 8-15 to INT 0x70-0x77. This conflicts with the ISRs
we programmed last lesson. Since we programmed ISRs 0-31, 
it is standard to remap the IRQs to ISRs 32-47.

The PICs are communicated with via I/O ports (see lesson 15).
The Master PIC has command 0x20 and data 0x21, while the slave has
command 0xA0 and data 0xA1.

The code for remapping the PICs is weird and includes
some masks, so check 
[this article](http://www.osdev.org/wiki/PIC) if you're curious.
Otherwise, just look at `cpu/isr.c`, new code after we set the IDT
gates for the ISRs. After that, we add the IDT gates for IRQs.

Now we jump to assembler, at `interrupt.asm`. The first task is to
add global definitions for the IRQ symbols we just used in the C code. 
Look at the end of the `global` statements.

Then, add the IRQ handlers. Same `interrupt.asm`, at the bottom. Notice
how they jump to a new common stub: `irq_common_stub` (next step)

We then create this `irq_common_stub` which is very similar to the ISR one.
It is located at the top of `interrupt.asm`, and it also defines
a new `[extern irq_handler]`

Now back to C code, to write the `irq_handler()` in `isr.c`. It sends some
EOIs to the PICs and calls the appropriate handler, which is stored in an array
named `interrupt_handlers` and defined at the top of the file. The new structs
are defined in `isr.h`. We will also use a simple function to register 
the interrupt handlers.

That was a lot of work, but now we can define our first IRQ handler!

There are no changes in `kernel.c`, so there is nothing new to run and see.
Please move on to the next lesson to check those shiny new IRQs.
