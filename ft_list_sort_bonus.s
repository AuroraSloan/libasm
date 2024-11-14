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
;rdx tmp

ft_list_sort:
	mov r8, rdi ;head
	mov r9, rsi ;cmp	
	xor r10, r10

	cmp qword [r8], 0
	je ret
	mov rdi, [r8]

	cmp qword [rdi + t_list_next_offset], 0
	je ret
	mov r11, rdi
	mov rsi, [rdi + t_list_next_offset]

insert_sort:
	call r9
	cmp rax, 0
	jng next_cmp

	; rsi to tmp rdx and set new rsi
	mov rdx, rsi
	mov rsi, [rsi + t_list_next_offset]
	mov [r11 + t_list_next_offset], rsi

	; set rdx before rdi
	mov [rdx + t_list_next_offset], rdi
	test r10, 0
	jmp update_head
	mov [r10 + t_list_next_offset], rdx

	jmp reset

next_cmp:
	test [rdi + t_list_next_offset], rsi
	jz next_node
	mov r10, rdi
	mov rdi, [rdi + t_list_next_offset]
	jmp insert_sort

next_node:
	mov r11, rsi
	mov rsi, [rsi + t_list_next_offset]
	jmp reset

update_head:
	mov [r8], rdx

reset:
	test rsi, 0
	jz ret
	xor r10, r10
	mov rdi, [r8]
	jmp insert_sort

ret:
	ret
