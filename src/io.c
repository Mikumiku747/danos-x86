//Use of the IO ports

#ifndef _IO_C
#define _IO_C

#include <stddef.h>
#include <stdint-gcc.h>

//Input from an IO port
static inline uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

//Output to an IO port
static inline void outb(uint16_t port, uint8_t val)
{
	asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

//Wait for an IO operation to finish
static inline void io_wait(void)
{
	/* Port 0x80 is used for 'checkpoints' during POST. */
	asm volatile ("outb %%al, $0x80" : : "a"(0));
}

#endif
