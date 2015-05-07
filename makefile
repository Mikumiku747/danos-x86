# Main DANOS Makefile
#####################

# Options
C-STANDARD = gnu99
CC = i686-elf-gcc
AS = i686-elf-as
BOCHS = bochs.exe
GRUB-MKRESCUE = grub-mkrescue
CFLAGS = -ffreestanding -O2 -Wall -Wextra -Werror -std=$(C-STANDARD)
BINVER = 0.1.3
ISOVER = $(BINVER)

# A list of all the source files the kernel uses
sourcefiles = \
	src/kernel.c \
	src/vga.c \
	src/io.c \
	src/mem.h \
	src/conversions.c \
	src/hardware.c \
	src/gdt.c \
	src/idt.c \
	src/irq.c

objectfiles = \
	build/boot.o \
	build/gdt.o \
	build/idt.o \
	build/kernel.o \
	build/irq.o \
	build/hardware.o

# The Multiboot Kernel Executable
bin/danos_v$(BINVER).bin: $(objectfiles) src/linker.ld
	#Build main kernel binary
	i686-elf-gcc -T src/linker.ld -o bin/danos_v$(BINVER).bin -ffreestanding -O2 -nostdlib $(objectfiles) -lgcc

isodir/boot/danos.bin: bin/danos_v$(BINVER).bin
	#Copy the binary into the ISO creation folder
	cp bin/danos_v$(BINVER).bin isodir/boot/danos.bin

# Phony targets
.PHONY: clean iso test

# Clean out build directory
objs = $(wildcard build/*.o)
clean:
	#Cleaning out built files
	rm $(objs)
	rm bin/danos_v$(BINVER).bin
	rm bin/danos_v$(ISOVER).iso

# Build an ISO, and put it in the bin folder
iso: bin/danos_v$(ISOVER).iso
bin/danos_v$(ISOVER).iso: isodir/boot/danos.bin isodir/boot/grub/grub.cfg
	#Build an ISO from our kernel binary
	$(GRUB-MKRESCUE) --output=bin/danos_v$(ISOVER).iso isodir

# Run the ISO in bochs
test: bin/danos_v$(ISOVER).iso
	#Run the ISO on bochs
	$(BOCHS) -q -f test_rig.bxrc

# Compile the assembly code files
build/boot.o: src/boot.s
	i686-elf-as src/boot.s -o build/boot.o
build/gdt.o: src/gdt.s
	i686-elf-as src/gdt.s -o build/gdt.o
build/idt.o: src/idt.s
	i686-elf-as src/idt.s -o build/idt.o
build/irq.o: src/irq.s
	i686-elf-as src/irq.s -o build/irq.o
build/hardware.o: src/hardware.s
	i686-elf-as src/hardware.s -o build/hardware.o

# Compile the kernel
build/kernel.o: $(sourcefiles)
	#Compiling kernel object
	i686-elf-gcc -c src/kernel.c -o build/kernel.o $(CFLAGS)
