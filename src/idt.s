#IDT
#Assembly routine for loading a new IDT

idt_load:
	lidt (idtp) #Load in the pointer to the new IDT
	ret

.global idt_load
.extern idtp
