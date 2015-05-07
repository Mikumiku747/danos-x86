#GDT
#Assembly routines for loading our new custom GDT

gdt_flush:
	lgdt (gp) #Load the new GDT pointer
	mov $0x10, %ax #0x10 or 16 is the data segment in our GDT
	mov %ax, %ds #Fill all the data segment registers with our new data segment
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	#We're going to fill the code segment register by doing a far jump
	ljmp $0x8, $flush_end #Jump to flush_end, but in segment 8h
flush_end:
	ret

.global gdt_flush
