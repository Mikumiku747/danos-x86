#Interrupt Request Handlers

.extern keyboard_interrupt

.align 4
handle_kbd:
	push %eax #Preserve all the registers
	push %ecx
	push %edx
	push %ebx
	push %esp
	push %ebp
	push %esi
	push %edi
    cld /* C code following the sysV ABI requires DF to be clear on function entry */
    call keyboard_interrupt
    pop %edi #Get them back
	pop %esi
	pop %ebp
	pop %esp
	pop %ebx
	pop %edx
	pop %ecx
	pop %eax
    iret

.align 4
handle_pit:
	push %eax #Preserve all the registers
	push %ecx
	push %edx
	push %ebx
	push %esp
	push %ebp
	push %esi
	push %edi
    cld /* C code following the sysV ABI requires DF to be clear on function entry */
    call PIT_interrupt
    pop %edi #Get them back
	pop %esi
	pop %ebp
	pop %esp
	pop %ebx
	pop %edx
	pop %ecx
	pop %eax
    iret


.align 4
double_fault:
	push %eax #Preserve all the registers
	push %ecx
	push %edx
	push %ebx
	push %esp
	push %ebp
	push %esi
	push %edi
    cld /* C code following the sysV ABI requires DF to be clear on function entry */
    call doublefault_interrupt
    pop %edi #Get them back
	pop %esi
	pop %ebp
	pop %esp
	pop %ebx
	pop %edx
	pop %ecx
	pop %eax
    iret

.align 4
general_protection_fault:
	push %eax #Preserve all the registers - Used to find the stack in the debugger
	push %ecx
	push %edx
	push %ebx
	push %esp
	push %ebp
	push %esi
	push %edi
    cld /* C code following the sysV ABI requires DF to be clear on function entry */
    call generalprotectionfault_interrupt
    pop %edi #Get them back
	pop %esi
	pop %ebp
	pop %esp
	pop %ebx
	pop %edx
	pop %ecx
	pop %eax
    iret

.global handle_kbd
.global handle_pit
.global double_fault
.global general_protection_fault
