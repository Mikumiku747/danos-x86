#ifndef KERNEL_C
#define KERNEL_C

#include <stddef.h>
#include <stdint-gcc.h>
#include "mem.h"
#include "io.c"
#include "conversions.c"
#include "hardware.c"
#include "gdt.c"
#include "idt.c"
#include "irq.c"
#include "vga.c"
#include "PIC8259.c"

//Test out our assembly functions
extern int Sum();
extern int LifeUniverseAndEverything();

int counter(int limit) {
	int count = 0;
	char countstr[] = "0000000";
	terminal_writestring("[Counter] Counter Program Started\n");
	while (count<limit) {
		inttostr(count, countstr);
		terminal_writestring("[Counter] ");
		terminal_writestring(countstr);
		terminal_writestring("\n");
		count++;
	}
	terminal_writestring("[Counter] Counter Program Finished\n");
	return 0;
}

void lookaroundyou() {
	while (1) {
		terminal_writestring("look around you, ");
	}
}

volatile char command_buffer[80 * 25];
volatile int current_char = 0;

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main()
{
	terminal_initialize(make_color(COLOR_RED, COLOR_LIGHT_GREY));
	//Load our own GDT and IDT
	terminal_writestring("Installing GDT...");
	gdt_install();
	terminal_writestring("Done\n");
	terminal_writestring("Remapping the PICs...");
	PIC_remap(0x20, 0x28);
	terminal_writestring("Done\n");

	terminal_writestring("Installing IDT...");
	idt_install();
	terminal_writestring("Done\n");

	//Mask ALL interrupts, so we don't need to ourselves
	for (int line = 0; line < 16; line++) {
		PIC_set_mask(line);
	}
	
	terminal_writestring("DANOS is booting, please wait...\n");

	//Test our numconverison function
	int testnum = Sum(221, 15);
	char teststr[] = "-------";
	inttostr(testnum, teststr);
	terminal_writestring("Testing conversion, testnum is :");
	terminal_writestring(teststr);
	terminal_writestring("\n");

	//Find the answer
	terminal_writestring("The answer to life, the universe and everything: ");
	int answer = LifeUniverseAndEverything();
	char answer_str[] = "-------";
	inttostr(answer, answer_str);
	terminal_writestring(answer_str);
	terminal_putchar('\n');

	if (testOpMode()) {
		terminal_writestring("Running in Protected Mode\n");
	}
	else {
		terminal_writestring("Running in Real Mode\n");
	}

	testCPUManufacturer();
	
	//counter(3);

	//Set up the command buffer
	for (int i = 0; i < 80 * 25; i++) {
		command_buffer[i] = 0; //Zero the character buffer
	}

	terminal_writestring("Enabling keyboard input...");
	asm("STI");
	PIC_clear_mask(1);
	terminal_writestring("Done\n");
	terminal_setcolor(make_color(COLOR_CYAN, COLOR_LIGHT_GREY));
	terminal_writestring("Now waiting for keyboard input:\n>>>");
	//lookaroundyou(); //For shits and giggles
	//asm("int $0x21"); //For testing interrupts

	while (1) {
		while (command_buffer[current_char-1] != '\n' || current_char > 1999) { //Wait for the user to make a newline
			terminal_putentryat(command_buffer[current_char-1], make_color(COLOR_WHITE, COLOR_BLACK), 0, 0); //Debug the last entered character in the meantime
			terminal_putentryat((current_char) + '0', make_color(COLOR_WHITE, COLOR_BLACK), 0, 1); //Debug how far along the current char is
		}
		terminal_writestring("-> ");
		for (int i = 0; i < current_char; i++) {
			terminal_putchar(command_buffer[i]); //Print off thier command
		}
		terminal_writestring(">>>");
		for (int i = 0; i < 80 * 25; i++) {
			command_buffer[i] = 0; //Zero the character buffer
		}
		current_char = 0;
	}
	//Kernel is done
	terminal_writestring("\nKernel finished execution, hanging!");
}
#endif
