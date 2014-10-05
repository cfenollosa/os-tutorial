*Concepts you may want to Google beforehand: control structures,
function calling, strings*

**Goal: Learn how to code basic stuff (loops, functions) with the assembler**

We are close to our definitive boot sector.

In lesson 7 we will start reading from the disk, which is the last step before
loading a kernel. But first, we will write some code with control structures,
function calling, and full strings usage. We really need to be comfortable with
those concepts before jumping to the disk and the kernel.


Strings
-------

Define strings like bytes, but terminate them with a null-byte (yes, like C)
to be able to determine their end.

```nasm
mystring:
    db 'Hello, World', 0
```

Notice that text surrounded with quotes is converted to ASCII by the assembler,
while that lone zero will be passed as byte `0x00` (null byte)


Control structures
------------------

We have already used one: `jmp $` for the infinite loop.

Assembler jumps are defined by the *previous* instruction result. For example:

```nasm
cmp ax, 4      ; if ax = 4
je ax_is_four  ; do something (by jumping to that label)
jmp else       ; else, do another thing
jmp endif      ; finally, resume the normal flow

ax_is_four:
    .....
    jmp endif

else:
    .....
    jmp endif  ; not actually necessary but printed here for completeness

endif:
```

Think in your head in high level, then convert it to assembler in this fashion.

There are many `jmp` conditions: if equal, if less than, etc. They are pretty 
intuitive but you can always Google them


Calling functions
-----------------

As you may suppose, calling a function is just a jump to a label.

The tricky part are the parameters. There are two steps to working with parameters:

1. The programmer knows they share a specific register or memory address
2. Write a bit more code and make function calls generic and without side effects

Step 1 is easy. Let's just agree that we will use `al` (actually, `ax`) for the parameters.

```nasm
mov al, 'X'
jmp print
endprint:

...

print:
    mov ah, 0x0e  ; tty code
    int 0x10      ; I assume that 'al' already has the character
    jmp endprint  ; this label is also pre-agreed
```

You can see that this approach will quickly grow into spaghetti code. The current
`print` function will only return to `endprint`. What if some other function
wants to call it? We are killing code reusage.

The correct solution offers two improvements:

- We will store the return address so that it may vary
- We will save the current registers to allow subfunctions to modify them
  without any side effects

To store the return address, the CPU will help us. Instead of using a couple of
`jmp` to call subroutines, use `call` and `ret`.

To save the register data, there is also a special command which uses the stack: `pusha`
and its brother `popa`, which pushes all registers to the stack automatically and
recovers them afterwards.


Including external files
------------------------

I assume you are a programmer and don't need to convince you why this is
a good idea.

The syntax is
```nasm
%include "file.asm"
```


Printing hex values
-------------------

In the next lesson we will start reading from disk, so we need some way
to make sure that we are reading the correct data. File `boot_sect_print_hex.asm`
extends `boot_sect_print.asm` to print hex bytes, not just ASCII chars.


Code! 
-----

Let's jump to the code. File `boot_sect_print.asm` is the subroutine which will
get `%include`d in the main file. It uses a loop to print bytes on screen.
It also includes a function to print a newline. The familiar `'\n'` is
actually two bytes, the newline char `0x0A` and a carriage return `0x0D`. Please
experiment by removing the carriage return char and see its effect.

As stated above, `boot_sect_print_hex.asm` allows for printing of bytes.

The main file `boot_sect_main.asm` loads a couple strings and bytes,
calls `print` and `print_hex` and hangs. If you understood
the previous sections, it's quite straightforward.
