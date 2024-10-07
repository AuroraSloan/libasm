BITS 64

section .note.GNU-stack

section .text
global ft_read

ft_read:
; args rdi, rsi, rdx
	mov rax, 0
	syscall
	test rax, rax
	js error
	ret

error:
	mov rax, -1
	ret
