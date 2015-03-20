*Concepts you may want to Google beforehand: CPU timer, keyboard interrupts, scancode*

**Goal: Implement our first IRQ handlers: the CPU timer and the keyboard**

Everything is now ready to test our hardware interrupts.

Timer
-----

The timer is easy to configure. First we'll declare an `init_timer()` on `cpu/timer.h` and
implement it on `cpu/timer.c`. It is just a matter of computing the clock frequency and
sending the bytes to the appropriate ports.

We will now fix `kernel/utils.c int_to_ascii()` to print the numbers in the correct order.
For that, we need to implement `reverse()` and `strlen()`.

Finally, go back to the `kernel/kernel.c` and do two things. Enable interrupts again
(very important!) and then initialize the timer interrupt.

Go `make run` and you'll see the clock ticking!


Keyboard
--------

The keyboard is even easier, with a drawback. The PIC does not send us the ASCII code
for the pressed key, but the scancode for the key-down and the key-up events, so we
will need to translate those.

Check out `drivers/keyboard.c` where there are two functions: the callback and
the initialization which configures the interrupt callback. A new `keyboard.h` was
created with the definitions.

`keyboard.c` also has a long table to translate scancodes to ASCII keys. For the time
being, we will only implement a simple subset of the US keyboard. You can read
more [about scancodes here](http://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html)

I don't know about you, but I'm thrilled! We are very close to building a simple shell.
In the next chapter, we will expand a little bit on keyboard input
