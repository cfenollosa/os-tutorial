*Concepts you may want to Google beforehand: scroll*

**Goal: Scroll the screen when the text reaches the bottom**

For this short lesson, open `drivers/screen.c` and note that at the
bottom of `print_char` there is a new section (line 84) which checks
if the current offset is over the screen size and scrolls the text.

The actual scrolling is handled by a new function, `memory_copy`. It is
a simpler version of the standard `memcpy` but we named it differently
to avoid namespace collisions, at least for now. Open `kernel/util.c` to
see its implementation.

To help visualize scrolling, we will also implement a function to
convert integers to text, `int_to_ascii`. Again, it is a quick implementation
of the standard `itoa`. Notice that for integers which have double digits
or more, they are printed in reverse. This is intended. On future lessons
we will extend our helper functions, but that is not the point for now.

Finally, open `kernel/kernel.c`. Initially, each line displays its line
number. You can set a breakpoint on line 14 to confirm this. Then,
the following `kprint`s force the kernel to scroll down.

This lesson ends the coverage for the os-dev.pdf document. From now on, we'll
follow [the OSDev wiki](http://wiki.osdev.org/Meaty_Skeleton) and
other sources and examples. Thanks Prof. Blundell for that great document!
