#Hardware routines

hang_cpu: #Hangs the CPU, effectively stops the computer
	cli
	hlt
	jmp hang_cpu

Sum:
	mov -4(%ebp), %eax
	mov -4(%ebp), %ebx
	add %ebx, %eax
	ret

LifeUniverseAndEverything:
	push %ebp
	mov $42, %eax
	pop %ebp
	ret

.global hang_cpu
.global Sum
.global LifeUniverseAndEverything
