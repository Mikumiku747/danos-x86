//IDT
/*
Functions for creating, loading and modifiying the Interrupt Descriptor Table
*/

#ifndef IDT_C
#define IDT_C

#include "irq.c"

/* Defines an IDT entry */
struct idt_entry
{
	unsigned short base_lo;
	unsigned short sel;        /* Our kernel segment goes here! */
	unsigned char always0;     /* This will ALWAYS be set to 0! */
	unsigned char flags;       /* Set using the above table! */
	unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

/* Declare an IDT of 256 entries. Although we will only use the
*  first 32 entries in this tutorial, the rest exists as a bit
*  of a trap. If any undefined IDT entry is hit, it normally
*  will cause an "Unhandled Interrupt" exception. Any descriptor
*  for which the 'presence' bit is cleared (0) will generate an
*  "Unhandled Interrupt" exception */
struct idt_entry idt[256];
struct idt_ptr idtp;

/* This exists in 'idt.s', and is used to load our IDT */
extern void idt_load();

/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
	//Set Base
	idt[num].base_lo = base & 0xFFFF;
	idt[num].base_hi = (base >> 16) & 0xFFFF;
	//Set Selector (Kernel code segment)
	idt[num].sel = sel;
	idt[num].always0 = 0;
	//Set flags
	idt[num].flags = flags;
}

/* Installs the IDT */
void idt_install()
{
	/* Sets the special IDT pointer up, just like in 'gdt.c' */
	idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
	idtp.base = (unsigned int)&idt;

	/* Clear out the entire IDT, initializing it to zeros */
	memset(&idt, 0, sizeof(struct idt_entry) * 256);

	/* Add any new ISRs to the IDT here using idt_set_gate */
	idt_set_gate(0x8, (unsigned long)&double_fault, 0x08, 0x8E); //Double fault exception
	idt_set_gate(0xD, (unsigned long)&general_protection_fault, 0x08, 0x8E); //Double fault exception
	idt_set_gate(0x20, (unsigned long)&handle_pit, 0x08, 0x8E); //Keyboard Handler
	idt_set_gate(0x21, (unsigned long)&handle_kbd, 0x08, 0x8E); //Keyboard Handler

	/* Points the processor's internal register to the new IDT */
	idt_load();
}

#endif
