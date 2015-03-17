
Everything is now ready to test our hardware interrupts.

Timer
-----

The timer is easy to configure. First we'll declare an `init_timer()` on `cpu/timer.h` and
implement it on `cpu/timer.c`. It is just a matter of computing the clock frequency and
sending the bytes to the appropriate ports.

## se printa gibberish, pq? mirar primero si se arregla con un kprint_int
## yo tenia una funcion que printaba enteros??!!! pero al rever. hacerla ahora bien y
## en el proximo episodio limpiar codigo y crear una libc


Finally, go back to the `kernel/kernel.c` and do two things. Enable interrupts again
(very important!) and then initialize the timer interrupt.

Go `make run` and you'll see the clock ticking! Unfortunately we are not printing the correct values
on screen, so we'll go ahead to `drivers/screen.c` and add a new `kprint_int()` method, also declaring
it on `drivers/screen.h`
