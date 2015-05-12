//IRQ
//Interrupt request handler functions

#ifndef _IRQ_C
#define _IRQ_C

#define KBD_PORT 0x60
#define KBD_LEDS 0xED

#include "vga.c"
#include "idt.c"
#include "PIC8259.c"


extern void handle_kbd();
extern void handle_pit();
extern void double_fault();
extern void general_protection_fault();

extern void hang_cpu(); //From hardware.s
extern volatile char command_buffer[];
extern volatile int current_char;
extern int increment_test;

char keymap_lower[] = "##1234567890-=\b\tqwertyuiop[]\n#asdfghjkl;\'`#\\zxcvbnm,./#*# #1234567890##789-456+1230.###AB";
char keymap_upper[] = "##!@#$%^&*()_+\b\tQWERTYUIOP{}\n#ASDFGHJKL:\"~#|ZXCVBNM<>?#*# #1234567890##789-456+1230.###AB";

int SHIFT = 0;
int CAPSLOCK = 0;
int NUMLOCK = 0;

void keyboard_interrupt() {
	uint8_t kbd_code = inb(KBD_PORT);
	switch (kbd_code) {
	case 0x2A:
		SHIFT = 1;
		break;
	case 0xAA:
		SHIFT = 0;
		break;
	case 0xBA:
		if (CAPSLOCK) {
			CAPSLOCK = 0;
		}
		else {
			CAPSLOCK = 1;
		}
		outb(KBD_PORT, KBD_LEDS);
		io_wait();
		outb(KBD_PORT, 4 * CAPSLOCK + 2 * NUMLOCK + 0);
		inb(KBD_PORT);
		break;
	case 0x3A:
		break;
	default:
		if (!(kbd_code & 0x80)) {
			if ((!SHIFT && !CAPSLOCK) || (SHIFT && CAPSLOCK)) {
				terminal_putchar(keymap_lower[kbd_code]);
				command_buffer[current_char] = keymap_lower[kbd_code];
			}
			else {
				terminal_putchar(keymap_upper[kbd_code]);
				command_buffer[current_char] = keymap_upper[kbd_code];
			}
			current_char++;
		}
		break;
	}
	PIC_sendEOI(1); //Send the END_OF_INTERRUPT code to the PIC, so it can let a new interrupt through
}

void PIT_interrupt() {
	terminal_putentryat((current_char)+'0', make_color(COLOR_WHITE, COLOR_BLACK), 0, 3);
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
