**Goal: Update our build system to El Capitan**

If you were following this guide from the beginning and upgraded to El Capitan only
to find that Makefiles don't compile anymore, follow these instructions to upgrade
your cross-compiler.

Otherwise, move on to the next lesson

Upgrading the cross-compiler
----------------------------

We will follow the same instructions as in lesson 11, more or less.

First, run `brew upgrade` and you will get your gcc upgraded to version 5.0 (at the time this guide was written)

Then run `xcode-select --install` to update OSX commandline tools

Once installed, find where your packaged gcc is (remember, not clang) and export it. For example:

```
export CC=/usr/local/bin/gcc-5
export LD=/usr/local/bin/gcc-5
```

We will need to recompile binutils and our cross-compiled gcc. Export the targets and prefix:

```
export PREFIX="/usr/local/i386elfgcc"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"
```

binutils
--------

Remember: always be careful before pasting walls of text from the internet. I recommend copying line by line.

```sh
mkdir /tmp/src
cd /tmp/src
curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.24.tar.gz # If the link 404's, look for a more recent version
tar xf binutils-2.24.tar.gz
mkdir binutils-build
cd binutils-build
../binutils-2.24/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX 2>&1 | tee configure.log
make all install 2>&1 | tee make.log
```


gcc
---
```sh
cd /tmp/src
curl -O http://mirror.bbln.org/gcc/releases/gcc-4.9.1/gcc-4.9.1.tar.bz2
tar xf gcc-4.9.1.tar.bz2
mkdir gcc-build
cd gcc-build
../gcc-4.9.1/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-libssp --enable-languages=c --without-headers
make all-gcc 
make all-target-libgcc 
make install-gcc 
make install-target-libgcc 
```


Now try to type `make` on this lesson's folder and check that everything compiles smoothly
