BITS 64

section .note.GNU-stack	

section .text
global ft_write
extern errno

ft_write:
	mov rax, 1
	syscall
	test rax, rax
	js error
	ret

error:
	neg rax
	mov [rel errno], rax
	mov rax, -1
	ret
