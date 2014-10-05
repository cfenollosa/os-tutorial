*Concepts you may want to Google beforehand: memory offsets, pointers*

The only goal of this lesson is to learn where the boot sector is stored

Please open page 14 [of this document](
http://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)<sup>1</sup>
and look at the figure with the memory layout.

I could just go ahead and tell you that it starts at `0x7C00`, but it's
better with an example.

We want to print an X on screen. We will try 4 different strategies
and see which ones work and why.

First, we will define the X as data, with a label:
```nasm
the_secret:
    db "X"
```

Then we will try to access `the_secret` in many different ways:

1. `mov al, the_secret`
2. `mov al, [the_secret]`
3. `mov al, the_secret + 0x7C00`
4. `mov al, 2d + 0x7C00`, where `2d` is the actual position of the X in the binary

Take a look at the code and read the comments.

Compile and run the code. You should see a string similar to `1[2¢3X4X`, where
the bytes following 1 and 2 are just random garbage.

If you add or remove instructions, remember to compute the new offset of the X
by counting the bytes, and replace `0x2d` with the new one.

~~~~~

[1] This whole tutorial is heavily inspired on that document. Please read the
root-level README for more information on that.
