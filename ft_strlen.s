BITS 64

section .note.GNU-stack

section .text
global ft_strlen

ft_strlen:
	mov rcx, 0

search_null:
	cmp byte [rdi + rcx], 0
	je return_value 
	inc rcx
	jmp search_null

return_value:
	mov rax, rcx
	ret
