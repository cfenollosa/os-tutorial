os-tutorial
===========

How to create an OS from scratch!

I have always wanted to learn how to make an OS from scratch. In college I was taught
how to implement advanced features (pagination, semaphores, memory management, etc)
but:

- I never got to start from my own boot sector
- College is hard so I don't remember most of it.
- I'm fed up with people who think that reading an already existing kernel, even if small, is 
a good idea to learn operating systems.

Inspired by [this document](http://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
and the [OSDev wiki](http://wiki.osdev.org/), I'll try to make short step-by-step READMEs and
code samples for anybody to follow. Honestly, this tutorial is basically the first document but
split into smaller pieces and without the theory.

Updated: more sources: [the little book about OS development](https://littleosbook.github.io),
[JamesM's kernel development tutorials](https://web.archive.org/web/20160412174753/http://www.jamesmolloy.co.uk/tutorial_html/index.html)


Features
--------

- This course is a code tutorial aimed at people who are comfortable with low level computing. For example,
programmers who have curiosity on how an OS works but don't have the time or willpower to start reading the Linux kernel
top to bottom.
- There is little theory. Yes, this is a feature. Google is your theory lecturer. Once you pass college, 
excessive theory is worse than no theory because it makes things seem more difficult than they really are.
- The lessons are tiny and may take 5-15 minutes to complete. Trust me and trust yourself. You can do it!


How to use this tutorial
------------------------

1. Start with the first folder and go down in order. They build on previous code, so if 
you jump right to folder 05 and don't know why there is a `mov ah, 0x0e`, it's because you missed lecture 02.
Really, just go in order. You can always skip stuff you already know.

2. Open the README and read the first line, which details the concepts you should be familiar with
before reading the code. Google concepts you are not familiar with. The second line states the goals for each lesson. 
Read them, because they explain why we do what we do. The "why" is as important as the "how".
 
3. Read the rest of the README. It is **very concise**.

4. (Optional) Try to write the code files by yourself after reading the README.

5. Look at the code examples. They are extremely well commented.

6. (Optional) Experiment with them and try to break things. The only way to make sure you understood something is
trying to break it or replicate it with different commands.


TL;DR: First read the README on each folder, then the code files. If you're brave, try to code them yourself.


Strategy
--------

We will want to do many things with our OS:

- Boot from scratch, without GRUB - DONE!
- Enter 32-bit mode - DONE
- Jump from Assembly to C - DONE!
- Interrupt handling - DONE!
- Screen output and keyboard input - DONE!
- A tiny, basic `libc` which grows to suit our needs - DONE!
- Memory management
- Write a filesystem to store files
- Create a very simple shell
- User mode
- Maybe we will write a simple text editor
- Multiple processes and scheduling

Probably we will go through them in that order, however it's soon to tell.

If we feel brave enough:

- A BASIC interpreter, like in the 70s!
- A GUI
- Networking



Contributing
------------

This is a personal learning project, and even though it hasn't been updated for a long time, I still have hopes to get into it at some point.

I'm thankful to all those who have pointed out bugs and submitted pull requests. I will need some time to review everything and I cannot guarantee that at this moment.

Please feel free to fork this repo. If many of you are interested in continuing the project, let me know and I'll link the "main fork" from here.
