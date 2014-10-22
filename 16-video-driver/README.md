*Concepts you may want to Google beforehand: VGA character cells, screen offset*

**Goal: Write strings on the screen**

Finally, we are going to be able to output text on the screen. This lesson contains
a bit more code than usual, so let's go step by step.

Open `drivers/screen.h` and you'll see that we have defined some constants for the VGA
card driver and three public functions, one to clear the screen and another couple
to write strings, the famously named `kprint` for "kernel print"

Now open `drivers/screen.c`. It starts with the declaration of private helper functions
that we will use to aid our `kprint` kernel API.

There are the two I/O port access routines that we learned in the previous lesson,
`get` and `set_cursor_offset()`.

Then there is the routine that directly manipulates the video memory, `print_char()`

Finally, there are three small helper functions to transform rows and columns into offsets
and vice versa.


kprint_at
---------

`kprint_at` may be called with a `-1` value for `col` and `row`, which indicates that
we will print the string at the current cursor position.

It first sets three variables for the col/row and the offset. Then it iterates through
the `char*` and calls `print_char()` with the current coordinates.

Note that `print_char` itself returns the offset of the next cursor position, and we reuse
it for the next loop.

`kprint` is basically a wrapper for `kprint_at`



print_char
----------

Like `kprint_at`, `print_char` allows cols/rows to be `-1`. In that case it retrieves
the cursor position from the hardware, using the `ports.c` routines.

`print_char` also handles newlines. In that case, we will position the cursor offset
to column 0 of the next row. 

Remember that the VGA cells take two bytes, one for the character itself and another one
for the attribute.


kernel.c
--------

Our new kernel is finally able to print strings.

It tests correct character positioning, spanning through multiple lines, line breaks,
and finally it tries to write outside of the screen bounds. What happens then?

In the next lesson we will learn how to scroll the screen.
