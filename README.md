#DANOS x86

##Introduction

This is just some little side thing I made one time, since I like embedded applications. Maybe I'll actually use branches this time as well. Ideally, in the end I want to make my own compiler for crappy little assembler abstracted programs in my own language (Similar to BASIC). But for now, it's jsut humble beginnings.

##Requirements
If you want to build and use this yourself, you're going to need some stuff, depending on what you want to do:

###Compile a binary
To compile a binary, which you can run with QEMU, you'll need:

 - Binutils, and
 - gcc

which both need to be targeted at i686-elf (You'll need a cross compiler, look on osdev.org for help). The Makefile expects it can just run i686-efl-gcc and everything will work, so have a look at the makefile if you have special needs. 

###Compile a bootable disk image
You'll need  GRUB utilities, and you need to go into the makefile and set GRUB-MKRECUE to something useful.

###Test it out in bochs
If you want to test it out in bochs, you'll need to install bochs and set the executeable for it in the makefile

##Usage
To build a binary, you can just run make, but in order to have a bootable CD, you'll need to run

    make iso

and to run a build and test it in bochs, you can run

    make test

which starts the built kernel in bochs, for convenience. 

##Changelist

V0.1.1:
 - Added basic test writing
 - Set up my own GDT and IDT

V0.1.2:
 - Added interrupt handlers for General protection fault, double fault, and keyboard
 - Typing now puts keys on the terminal

V0.1.3:
 - Added input processing, it can now tell what you typed in, kind of...
