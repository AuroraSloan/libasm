BITS 64

section .note.GNU-stack

section .text
global ft_list_push_front

%define t_list_data_offset 0
%define t_list_next_offset 8
%define t_list_size 16
%define ENOMEM 12

extern __errno_location
extern malloc

ft_list_push_front:
	test rdi, rdi
	jz err
	test rsi, rsi
	jz err

	push rdi
	push rsi

	mov rdi, t_list_size
	call malloc wrt ..plt

	pop rsi
	pop rdi
	test rax, rax
	jz sys_err

	mov r8, [rdi]
	mov [rax + t_list_next_offset], r8
	mov [rax + t_list_data_offset], rsi
	mov [rdi], rax
	ret

sys_err:
	call __errno_location wrt ..plt
	mov qword [rax], ENOMEM

err:
	ret
