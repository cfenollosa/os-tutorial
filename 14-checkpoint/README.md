*Concepts you may want to Google beforehand: monolithic kernel, microkernel, debugger, gdb*

**Goal: Pause and organize our code a little bit. Then learn how to debug the kernel with gdb**

Maybe you didn't realize it, but you already have your own kernel
running!

However, it does very little, just print an 'X'. Now is the time to stop for
a moment and organize the code into folders, create a scalable Makefile for future code,
and think on a strategy.

Take a look at the new folder structure. Most of the files have been symlinked
from previous lessons, so if we have to change them at some point, it will be
a better idea to remove the symlink and create a new file.

Furthermore, since from now on we will use mostly C to code, we'll take advantage of qemu's
ability to open a connection to gdb. First, let's install a cross-compiled `gdb` since
OSX uses `lldb` which is not compatible with the ELF file format (neither is the `gdb` available
on Homebrew's repos)

```sh
cd /tmp/src
curl -O http://ftp.rediris.es/mirror/GNU/gdb/gdb-7.8.tar.gz
tar xf gdb-7.8.tar.gz
mkdir gdb-build
cd gdb-build
export PREFIX="/usr/local/i386elfgcc"
export TARGET=i386-elf
../gdb-7.8/configure --target="$TARGET" --prefix="$PREFIX" --program-prefix=i386-elf-
make
make install
```

Check out the Makefile target `make debug`. This target uses builds `kernel.elf`, which
is an object file (not binary) with all the symbols we generated on the kernel, thanks to
the `-g` flag on gcc. Please examine it with `xxd` and you'll see some strings. Actually,
the correct way to examine the strings in an object file is by `strings kernel.elf`

We can take advantage of this cool qemu feature. Type `make debug` and, on the gdb shell:

- Set up a breakpoint in `kernel.c:main()`: `b main`
- Run the OS: `continue`
- Run two steps into the code: `next` then `next`. You will see that we are just about to set
  the 'X' on the screen, but it isn't there yet (check out the qemu screen)
- Let's see what's in the video memory: `print *video_memory`. There is the 'L' from "Landed in
  32-bit Protected Mode"
- Hmmm, let's make sure that `video_memory` points to the correct address: `print video_memory`
- `next` to put there our 'X'
- Let's make sure: `print *video_memory` and look at the qemu screen. It's definitely there.

Now is a good time to read some tutorial on `gdb` and learn super useful things like `info registers`
which will save us a lot of time in the future!


You may notice that, since this is a tutorial, we haven't yet discussed which kind
of kernel we will write. It will probably be a monolithic one since they are easier
to design and implement, and after all this is our first OS. Maybe in the future
we'll add a lesson "15-b" with a microkernel design. Who knows.
