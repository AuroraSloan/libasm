BITS 64

section .not.GNU-stack

section .text
global ft_list_sort

%define t_list_data_offset 0
%define t_list_next_offset 8

;r8 head
;r9 cmp func
;r10 rdi's prev
;r11 rsi's prev
;r12 rdi node
;r13 rsi node
;rdx tmp

ft_list_sort:
	test rdi, rdi
	jz ret
	test rsi, rsi
	jz ret
	push r12
	push r13

	mov r8, rdi ;head
	mov r9, rsi ;cmp
	xor r10, r10

	mov r12, [r8]
	test r12, r12
	jz ret
	lea rdi, [r12 + t_list_data_offset]

	mov r13, [rdi + t_list_next_offset]
	test r13, r13
	jz ret
	mov r11, r12
	lea rsi, [r13 + t_list_data_offset]

insert_sort:
	call r9
	cmp rax, 0
	jng next_cmp

	; rsi to tmp rdx and set new rsi
	mov rdx, r13
	mov r13, [r13 + t_list_next_offset]
	mov [r11 + t_list_next_offset], r13

	; set rdx before rdi
	mov [rdx + t_list_next_offset], r12
	test r10, r10
	jz update_head
	mov [r10 + t_list_next_offset], rdx

	jmp reset

next_cmp:
	cmp [r12 + t_list_next_offset], r13
	je next_node
	mov r10, r12
	mov r12, [r12 + t_list_next_offset]
	lea rdi, [r12 + t_list_data_offset]
	jmp insert_sort

next_node:
	mov r11, r13
	mov r13, [r13 + t_list_next_offset]	
	jmp reset

update_head:
	mov [r8], rdx

reset:
	test r13, r13
	jz ret
	lea rsi, [r13 + t_list_data_offset]
	xor r10, r10
	mov r12, [r8]
	lea rdi, [r12 + t_list_data_offset]
	jmp insert_sort

ret:
	pop r13
	pop r12
	ret
