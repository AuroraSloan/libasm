BITS 64

section .note.GNU-stack

section .text
global ft_list_remove_if

%define t_list_data_offset 0
%define t_list_next_offset 8

ft_list_remove_if:
	test rdi, rdi
	jz ret
	test rsi, rsi
	jz ret
	test rdx, rdx
	jz ret

	push rbx
	push r12
	push r13
	push r14
	push r15
	push rbp

	mov rbx, rdi ;head
	mov r12, rsi ;data
	mov r13, rdx ;cmp
	mov r14, rcx ;free
	mov r15, [rbx] ;node
	xor rbp, rbp ;prev

	mov rdi, [r15 + t_list_data_offset]

cmp:
	call r13
	test eax, eax
	jnz get_next

	mov rdi, r15
	mov r15, [r15 + t_list_next_offset]
	test rbp, rbp
	jz set_head
	mov [rbp + t_list_next_offset], r15
	jmp ft_free

set_head:
	mov [rbx], r15

ft_free:
	call r14
	jmp check_node

get_next:
	mov rbp, r15
	mov r15, [r15 + t_list_next_offset]

check_node:
	test r15, r15
	jz fin
	mov rdi, [r15 + t_list_data_offset]
	mov rsi, r12
	jmp cmp

fin:
	pop rbp
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx

ret:
	ret
