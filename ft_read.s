BITS 64

section .note.GNU-stack

section .text
global ft_read
extern __errno_location

ft_read:
	mov rax, 0
	syscall
	test rax, rax
	js error
	ret

error:
	neg rax
	mov rcx, rax
	call __errno_location wrt ..plt
	mov [rax], rcx
	mov rax, -1
	ret
