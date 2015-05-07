#ifndef _HARDWARE_C
#define _HARDWARE_C

#include <stddef.h>
#include <stdint-gcc.h>
#include "vga.c"

//Test CPU ID
void testCPUManufacturer() {
	uint32_t cpuid_code = 0;
	uint32_t cpuid_b;
	uint32_t cpuid_c;
	uint32_t cpuid_d;
	asm("mov $0, %%eax;"
		"cpuid"
		:"=b" (cpuid_b), "=c" (cpuid_c), "=d" (cpuid_d)
		: "a" (cpuid_code)
		);
	terminal_writestring("Testing CPU ID: ");
	terminal_putchar((char)(cpuid_b >> 0));
	terminal_putchar((char)(cpuid_b >> 8));
	terminal_putchar((char)(cpuid_b >> 16));
	terminal_putchar((char)(cpuid_b >> 24));
	terminal_putchar((char)(cpuid_d >> 0));
	terminal_putchar((char)(cpuid_d >> 8));
	terminal_putchar((char)(cpuid_d >> 16));
	terminal_putchar((char)(cpuid_d >> 24));
	terminal_putchar((char)(cpuid_c >> 0));
	terminal_putchar((char)(cpuid_c >> 8));
	terminal_putchar((char)(cpuid_c >> 16));
	terminal_putchar((char)(cpuid_c >> 24));
	terminal_putchar('\n');
}

//Test Mode
int testOpMode() {
	uint32_t mode;
	asm("movl %%cr0, %0"
		:"=a" (mode)
		);
	mode = mode & (uint32_t)1;
	return mode;
}

#endif
