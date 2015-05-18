*Concepts you may want to Google beforehand: malloc*

**Goal: Implement a memory allocator**

We will add a kernel memory allocator to `libc/mem.c`. It is 
implemented as a simple pointer to free memory, which keeps
growing.

The `kmalloc()` function can be used to request an aligned page,
and it will also return the real, physical address, for later use.

We'll change the `kernel.c` leaving all the "shell" code there,
Let's just try out the new `kmalloc()`, and check out that
our first page starts at 0x10000 (as hardcoded on `mem.c`) and
subsequent `kmalloc()`'s produce a new address which is
aligned 4096 bytes or 0x1000 from the previous one.

Note that we added a new `strings.c:hex_to_ascii()` for
nicer printing of hex numbers.

Another cosmetic modification is to rename `types.c` to 
`type.c` for language consistency.

The rest of the files are unchanged from last lesson.
