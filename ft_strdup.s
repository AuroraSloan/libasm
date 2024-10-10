BITS 64

section .note.GNU-stack

section .text
global ft_strdup
extern __errno_location
extern malloc

ft_strdup:
	mov rcx, 0

get_len:
	cmp byte [rdi + rcx], 0
	je alloc
	inc rcx
	jmp get_len

alloc:
	inc rcx
	push rdi
	mov rdi, rcx
	mov rax, [rel malloc wrt ..got]
	call rax
	test rax, rax
	je error
	xor rcx, rcx
	pop rdi

copy:
	mov sil, byte [rdi + rcx]
	mov byte [rax + rcx], sil
	cmp byte [rdi + rcx], 0
	je end
	inc rcx
	jmp copy

error:
	neg rax
	mov rcx, rax
	mov rax, [rel __errno_location wrt ..got]
	call rax
	mov [rax], rcx
	mov rax, 0

end:
	ret
