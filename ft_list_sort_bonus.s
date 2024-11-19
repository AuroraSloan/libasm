BITS 64

section .note.GNU-stack

section .text
global ft_list_sort

%define t_list_data_offset 0
%define t_list_next_offset 8

;rbx head
;rbp cmp func
;r12 rdi node
;r13 rsi node
;r14 rdi's prev
;r15 rsi's prev
;rdx tmp

ft_list_sort:
	push rbx
	push rbp
	push r12
	push r13
	push r14
	push r15

	test rdi, rdi
	jz ret
	test rsi, rsi
	jz ret

	mov rbx, rdi ;head
	mov rbp, rsi ;cmp
	xor r14, r14

	mov r12, [rbx]
	test r12, r12
	jz ret
	mov rdi, [r12 + t_list_data_offset]

	mov r13, [r12 + t_list_next_offset]
	test r13, r13
	jz ret
	mov r15, r12
	mov rsi, [r13 + t_list_data_offset]

insert_sort:
	push rdi
	push rsi
	call rbp
	pop rsi
	pop rdi
	cmp eax, 0
	jng next_cmp

	; rsi to tmp rdx and set new rsi
	mov rdx, r13
	mov r13, [r13 + t_list_next_offset]
	mov [r15 + t_list_next_offset], r13

	; set rdx before rdi
	mov [rdx + t_list_next_offset], r12
	test r14, r14
	jz update_head
	mov [r14 + t_list_next_offset], rdx

	jmp reset

next_cmp:
	cmp [r12 + t_list_next_offset], r13
	je next_node
	mov r14, r12
	mov r12, [r12 + t_list_next_offset]
	mov rdi, [r12 + t_list_data_offset]
	jmp insert_sort

next_node:
	mov r15, r13
	mov r13, [r13 + t_list_next_offset]	
	jmp reset

update_head:
	mov [rbx], rdx

reset:
	test r13, r13
	jz ret
	mov rsi, [r13 + t_list_data_offset]
	xor r14, r14
	mov r12, [rbx]
	mov rdi, [r12 + t_list_data_offset]
	jmp insert_sort

ret:
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbp
	pop rbx
	ret
