BITS 64

section .note.GNU-stack

section .text
global ft_strdup
extern __errno_location
extern malloc
%define ENOMEM 12

ft_strdup:
	xor rcx, rcx

get_len:
	cmp byte [rdi + rcx], 0
	je alloc
	inc rcx
	jmp get_len

alloc:
	inc rcx
	push rdi
	mov rdi, rcx
	call malloc wrt ..plt
	pop rdi
	test rax, rax
	jz error

	xor rcx, rcx

copy:
	mov sil, byte [rdi + rcx]
	mov byte [rax + rcx], sil
	cmp byte [rdi + rcx], 0
	je end
	inc rcx
	jmp copy

error:
	call __errno_location wrt ..plt
	mov qword [rax], ENOMEM
	mov rax, 0

end:
	ret
