BITS 64

section .note.GNU-stack

section .text
global ft_strcmp

ft_strcmp:
	xor rcx, rcx

cmp:
	mov al, byte [rdi + rcx]
	cmp al, byte [rsi + rcx]
	jb ret_not_equal
	ja ret_not_equal
	cmp al, 0
	je ret_equal
	inc rcx
	jmp cmp

ret_not_equal:
	sub al, byte[rsi + rcx]
	movsx rax, al
	ret

ret_equal:
	xor rax, rax
	ret
