BITS 64

section .note.GNU-stack

section .text
global ft_list_size

%define t_list_next_offset 8

ft_list_size:
	xor rax, rax
	mov r8, rdi

next:
	cmp r8, 0
	je ret
	inc rax
	mov r8, [r8 + t_list_next_offset]
	jmp next

ret:
	ret
