BITS 64

section .data
	hello db "Hello, world!", 0xa
	hello_len equ $ - hello
	buf db "00", 0xa

section .text
global _start

_start:

	mov rax, 1
	mov rdi, 1
	mov rsi, hello
	mov rdx, hello_len
	syscall

	mov rax, hello_len
	mov rdi, buf + 1

loop:
	xor rdx, rdx
	mov rcx, 10
	div rcx
	add dl, '0'
	mov [rdi], dl
	dec rdi
	test rax, rax
	jnz loop

	mov rax, 1
	mov rdi, 1
	mov rsi, buf
	mov rdx, 10
	syscall

	mov rax, 60
	mov rdi, 0
	syscall
