BITS 64

section .note.GNU-stack

section  .text
global ft_strcpy

ft_strcpy:
	xor rcx, rcx

cpy:
	mov al, byte [rsi + rcx]
	mov byte [rdi + rcx], al
	cmp al, 0
	je ret_ptr
	inc rcx
	jmp cpy

ret_ptr:
	mov rax, rdi
	ret
