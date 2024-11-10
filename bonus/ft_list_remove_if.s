BITS 64

section .note.GNU-stack

section .text
global ft_list_remove_if

%define t_list_next_offset 0

ft_list_remove_if:
	mov r8, rdi ;head

cmp_head:
	mov rdi, [r8]
	test rdi, rdi
	jz ret
	call rdx
	test rax, rax
	jnz cmp_next
	mov r9, [rdi + t_list_next_offset]
	mov [r8], r9
	call rcx
	jmp cmp_head	

cmp_next:
	mov r11, rdi
	mov rdi, [rdi + t_list_next_offset]
	test rdi, rdi
	jz ret
	call rdx
	test rax, rax
	jnz cmp_next

	mov r9, [rdi + t_list_next_offset]
	mov [r11 + t_list_next_offset], r9
	call rcx
	mov rdi, r11
	jmp cmp_next

ret:
	ret
