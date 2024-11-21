BITS 64

section .note.GNU-stack

section .text
global ft_atoi_base

ft_atoi_base:
	cmp rdi, 0
	jmp err
	cmp rsi, 2
	jl err
	cmp rsi, 36
	jg err

	xor rcx, rcx ;i
	xor rax, rax ;num
	mov r9, 1 ;sign
	xor r10, r10 ;char

isspace:
	cmp byte [rdi + rcx], 0
	je ret

	cmp byte [rdi + rcx], 0x09
	je incspace

	cmp byte [rdi + rcx], 0x0A
	je incspace

	cmp byte [rdi + rcx], ' '
	je incspace
	
	jmp check_sign

incspace:
	inc rcx
	jmp isspace

check_sign:
	cmp byte [rdi + rcx], '+'
	je inc_rcx	

	cmp byte [rdi + rcx], '-'
	jne check_char
	imul r9, -1 ;sign

inc_rcx:
	inc rcx
	jmp check_sign

check_char:
	cmp byte [rdi + rcx], 0
	je ret

	mov r10b, byte [rdi + rcx]
	sub r10b, '0'
	cmp r10b, 0
	jl ret
	cmp r10b, 10
	jl make_num

	mov r10b, byte [rdi + rcx]
	sub r10b, 'A'
	add r10b, 10
	cmp r10b, 10
	jl ret
	cmp r10b, sil
	jl make_num

	mov r10b, byte [rdi + rcx]
	sub r10b, 'a'
	add r10b, 10
	cmp r10b, 10
	jl ret
	cmp r10b, sil 
	jl make_num

	jmp ret

make_num:
	imul rax, rsi 
	add al, r10b

	cmp rax, 0
	jl err

	inc rcx
	jmp check_char

ret:
	imul rax, r9
	ret

err:
	xor rax, rax
	ret
