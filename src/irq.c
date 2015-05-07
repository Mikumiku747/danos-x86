//IRQ
//Interrupt request handler functions

#ifndef _IRQ_C
#define _IRQ_C

#define KBD_PORT 0x60

#include "vga.c"
#include "idt.c"
#include "PIC8259.c"


extern void handle_kbd();
extern void double_fault();
extern void general_protection_fault();

extern void hang_cpu(); //From hardware.s
extern char command_buffer[];
extern char *current_char;

char keymap_lower[] = "##1234567890-=\b\tqwertyuiop[]\n#asdfghjkl;\'`#\\zxcvbnm,./#*# #1234567890##789-456+1230.###AB";

void keyboard_interrupt() {
	uint8_t kbd_code = inb(KBD_PORT);
	if (!(kbd_code & 0x80)) {
		terminal_putchar(keymap_lower[kbd_code]);
		*current_char = keymap_lower[kbd_code];
		current_char++;
		terminal_putchar(*current_char);
	}
	PIC_sendEOI(1); //Send the END_OF_INTERRUPT code to the PIC, so it can let a new interrupt through
}

void divideByZeroError() {
	terminal_writestring("Divide by zero error! Oh noes!/n");
}

void doublefault_interrupt() {
	terminal_writestring("DOUBLE FAULT! Halting...\n");
	hang_cpu();
}

void generalprotectionfault_interrupt() {
	terminal_writestring("GENERAL PROTECTION FAULT! Halting...\n");
	hang_cpu();
}

#endif
