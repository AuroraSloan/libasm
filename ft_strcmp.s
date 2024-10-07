BITS 64

section .note.GNU-stack

section .text
global ft_strcmp

ft_strcmp:
	xor rcx, rcx

cmp:
	mov al, byte [rdi + rcx]
	cmp al, byte [rsi + rcx]
	jb ret_less
	ja ret_greater
	cmp al, 0
	je ret_equal
	inc rcx
	jmp cmp

ret_equal:
	mov rax, 0
	ret

ret_less:
	mov rax, -1
	ret

ret_greater:
	mov rax, 1
	ret
