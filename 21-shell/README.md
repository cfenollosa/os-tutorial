
**Goal: Clean the code a bit and parse user input**

In this lesson we will do two things. First, we will clean up the code a bit, so it is ready 
for further lessons. During the previous ones I tried to put things in the most predictable places,
but it is also a good exercise to know when the code base is growing and adapt it to current
and further needs.


Code cleaning
-------------

First of all, we will quickly start to need more utility functions
for handling strings and so on. In a regular OS, this is called the C library,
or libc for short.

Right now we have a `utils.c` which we will split into `mem.c` and `string.c`, with their respective headers.

Second, we will create a new function `irq_install()` so that the kernel
only needs to perform one call to initialize all the IRQs. That function
is akin to `isr_install()` and placed on the same `irq.c`.
While we're here, we will disable the `kprint()` on `timer_callback()`
to avoid filling the screen with junk, now that we know that it works
properly.

There is not a clear distinction between `cpu/` and `drivers/`.
Keep in mind that I'm
creating this tutorial while following many others, and each of them
has a distinct folder structure. The only change we will do for now is to
move `drivers/ports.*` into `cpu/` since it is clearly cpu-dependent code.
`boot/` is also CPU-dependent code, but we will not mess with it until
we implement the boot sequence for a different machine.

There are more switches for the `CFLAGS` on the `Makefile`, since we will now
start creating higher-level functions for our C library and we don't want
the compiler to include any external code if we make a mistake with a declaration.
We also added some flags to turn warnings into errors, since an apparently minor mistake
converting pointers can blow up later on. This also forced us to modify some misc pointer
declarations in our code.

Finally, we'll add a macro to avoid warning-errors on unused parameters on `libc/function.h`

Keyboard characters
-------------------

How to access the typed characters, then?

- When a key is pressed, the callback gets the ASCII code via a new
arrays which are defined at the beginning of `keyboard.c`
- The callback then appends that character to a buffer, `key_buffer`
- It is also printed on the screen
- When the OS wants to read user input, it calls `libc/io.c:readline()`

`keyboard.c` also parses backspace, by removing the last element
of the key buffer, and deleting it from the screen, by calling 
`screen.c:kprint_backspace()`. For this we needed to modify a bit
`print_char()` to not advance the offset when printing a backspace


Responding to user input
------------------------

The keyboard callback checks for a newline, and then calls the kernel,
telling it that the user has input something. Out final libc function
is `strcmp()`, which compares two strings and returns 0 if they
are equal. If the user inputs "END", we halt the CPU.

This is the most basic shell ever, but you should be proud, because
we implemented it from scratch. Do you realize how cool this is?

If you want to, expand `kernel.c` to parse more stuff. In the future,
when we have a filesystem, we will allow the user to run some basic commands.
