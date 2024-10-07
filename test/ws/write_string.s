BITS 64

section .note.GNU-stack

section .data
	string db "hello, world!", 0
	len equ $ - string

section .text
global write_string

write_string:

	mov rax, 1
	mov rdi, 1
	lea rsi, [rel string]
	mov rdx, len
	syscall

	mov rax, 60
	xor rdi, rdi
	syscall
