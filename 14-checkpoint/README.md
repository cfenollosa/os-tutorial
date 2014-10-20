*Concepts you may want to Google beforehand: monolithic kernel, microkernel*
**Goal: Pause and organize our code a little bit**

Maybe you didn't realize it, but you already have your own kernel
running!

However, it does very little, just print an 'X'. Now is the time to stop for
a moment and organize the code into folders, create a scalable Makefile for future code,
and think on a strategy.

Take a look at the new folder structure. Most of the files have been symlinked
from previous lessons, so if we have to change them at some point, it will be
a better idea to remove the symlink and create a new file.


Strategy
--------

We will want to do many things with our OS:

- Handle screen output and keyboard input, for starters
- A tiny, basic `libc`
- Memory management
- Interrupt handling
- Write a filesystem to store files
- Create a very simple shell
- Maybe we will write a simple text editor
- Multiple processes and scheduling

Probably we will go through them in that order, however it's soon to tell.

If we feel brave enough:

- A BASIC interpreter, like in the 70s!
- A GUI
- Networking


You may notice that, since this is a tutorial, we haven't yet discussed which kind
of kernel we will write. It will probably be a monolithic one since they are easier
to design and implement, and after all this is our first OS. Maybe in the future
we'll add a lesson "15-b" with a microkernel design. Who knows.
