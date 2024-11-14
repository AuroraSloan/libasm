BITS 64

section .note.GNU-stack

section .text
global ft_list_size

ft_list_size:
	xor rax, rax
	mov r8, rdi

next:
	cmp r8, 0
	je ret
	inc rax
	mov r8, [r8 + 8]
	jmp next

ret:
	ret
