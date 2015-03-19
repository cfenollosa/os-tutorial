*Concepts you may want to Google beforehand: CPU timer, keyboard interrupts*

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
