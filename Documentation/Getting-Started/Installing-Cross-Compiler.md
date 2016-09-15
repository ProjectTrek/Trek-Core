# Installing the Cross Compiler

A cross compiler is required to build Trek. A cross compiler is needed *unless you are developing from inside Trek*. However, because the project is in its infancy, this is unlikely.

# Pre-requisites

## Installing GCC and Build Essentials
Run the following commands to download and install GCC:

```shell
sudo apt-get install gcc build-essential make
```

## Installing ```wget``` and ```git```
Run the following commands to download and install ```wget``` and ```git```:

```shell
sudo apt-get install wget git
```

## Downloading requirements
Run the following commands to download the required files:

```shell
sudo apt-get install -y libgmp3-dev libmpfr-dev libisl-dev libcloog-isl-dev libmpc-dev texinfo
```

## Setting up workspace
Now we need to setup a build spot. Run these commands to create and populate a directory:

```bash
cd ~
mkdir cross-compiler-build
cd cross-compiler-build
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
```

## Build Binutils
```shell
cd $HOME/cross-compiler-build
wget http://ftp.gnu.org/gnu/binutils/binutils-2.27.tar.gz
tar xf binutils-2.27.tar.gz
mkdir build-binutils
cd build-binutils
../binutils-2.27/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
```

## Build GCC
```shell
cd $HOME/cross-compiler-build
wget http://mirrors.concertpass.com/gcc/releases/gcc-6.2.0/gcc-6.2.0.tar.gz
tar xf gcc-6.2.0.tar.gz
mkdir build-gcc
cd build-gcc
../gcc-6.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
```

## Fix $PATH
```shell
export PATH="$HOME/opt/cross/bin:$PATH"
```
