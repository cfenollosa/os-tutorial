*Concepts you may want to Google beforehand: interrupts, pipelining*

**Goal: Enter 32-bit protected mode and test our code from previous lessons**

To jump into 32-bit mode:

1. Disable interrupts
2. Load our GDT
3. Set a bit on the CPU control register `cr0`
4. Flush the CPU pipeline by issuing a carefully crafted far jump
5. Update all the segment registers
6. Update the stack
7. Call to a well-known label which contains the first useful code in 32 bits

We will encapsulate this process on the file `32bit-switch.asm`. Open it
and take a look at the code.

After entering 32-bit mode, we will call `BEGIN_PM` which is the entry point
for our actual useful code (e.g. kernel code, etc). You can read the code
at `32bit-main.asm`. Compile and run this last file and you will see the two 
messages on the screen.

Congratulations! Our next step will be to write a simple kernel
