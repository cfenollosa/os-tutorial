*Concepts you may want to Google beforehand: I/O ports*

**Goal: Learn how to use the VGA card data ports**

We will use C to communicate with devices via I/O registers and ports.

Open `drivers/ports.c` and examine the inline C assembler syntax. It has
some differences, like the order of the source and destination operands,
and the funny syntax to assign variables to operands.

When you understand the concepts, open `kernel/kernel.c` for an example
of use.

In this example we will examine the I/O ports which map the screen cursor
position. Specifically, we will query port `0x3d4` with value `14` to request
the cursor position high byte, and the same port with `15` for the low byte.

When this port is queried, it saves the result in port `0x3d5`

Don't miss the opportunity to use `gdb` to inspect the value of C variables,
since we still can't print them on the screen. To do so, set a breakpoint
for a specific line, `breakpoint kernel.c:21` and use the `print` command
to examine variables. Aren't you glad now that we invested some time in
compiling the cross-compiled gdb? ;)

Finally, we will use the queried cursor position to write a character
at that location.
