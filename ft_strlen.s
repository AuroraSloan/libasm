BITS 64

section .note.GNU-stack

section .text
global ft_strlen

ft_strlen:
	xor rcx, rcx
	cmp rdi, 0
	je ret

search_null:
	cmp byte [rdi + rcx], 0
	je ret
	inc rcx
	jmp search_null

ret:
	mov rax, rcx
	ret	
