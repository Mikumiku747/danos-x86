//Memory
/*
Memory related functions, such as setting, copying
*/

#ifndef _MEM_H
#define _MEM_H

//These functions courtesy of Brandon F. from OSDever.net
void *memcpy(void *dest, const void *src, size_t count)
{
	const char *sp = (const char *)src;
	char *dp = (char *)dest;
	for (; count != 0; count--) *dp++ = *sp++;
	return dest;
}

void *memset(void *dest, char val, size_t count)
{
	char *temp = (char *)dest;
	for (; count != 0; count--) *temp++ = val;
	return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
	unsigned short *temp = (unsigned short *)dest;
	for (; count != 0; count--) *temp++ = val;
	return dest;
}

#endif //_MEM_H