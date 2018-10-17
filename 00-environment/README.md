*Concepts you may want to Google beforehand: linux, mac, terminal, compiler, emulator, nasm, qemu*

**Goal: Install the software required to run this tutorial**

**NASM**

The Netwide Assembler (NASM) is an assembler and disassembler for the Intel x86 architecture. It can be used to write 16-bit, 32-bit (IA-32) and 64-bit (x86-64) programs. NASM is considered to be one of the most popular assemblers for Linux.

NASM was originally written by Simon Tatham with assistance from Julian Hall. As of 2016, it is maintained by a small team led by H. Peter Anvin. It is open-source software released under the terms of a simplified (2-clause) BSD license.

**QEMU**

QEMU is a free and open-source emulator that performs hardware virtualization.

QEMU is a hosted virtual machine monitor: it emulates the machine's processor through dynamic binary translation and provides a set of different hardware and device models for the machine, enabling it to run a variety of guest operating systems. It also can be used with KVM to run virtual machines at near-native speed (by taking advantage of hardware extensions such as IntelVT). QEMU can also do emulation for user-level processes, allowing applications compiled for one architecture to run on another.

I'm working on a Mac, though Linux is better because it will have all the standard tools already
available for you.

On a mac, [install Homebrew](http://brew.sh) and then `brew install qemu nasm`

Don't use the Xcode developer tools `nasm` if you have them installed, they won't work for the most cases. Always use `/usr/local/bin/nasm`

On Linux systems, use your prefered package manager to install `nasm`. For example, on Ubuntu:
  `$sudo apt install nasm`

If you want to build it by source, you might want to google how to do that.

The same as qemu:
  `$sudo apt install qemu`

To test whether installation is successful:
  `$ nasm -v`
  `NASM version x.xx.xx`

On some systems qemu is split into multiple binaries. You may want
to call `qemu-system-x86_64 binfile`
