BITS 64

section .note.GNU-stack

section .text
global ft_atoi_base

ft_atoi_base:
	xor rcx, rcx ;i
	xor rax, rax ;num
	xor r8, r8 ;base
	mov r9, 1 ;sign
	xor r10, r10 ;char

isbase:
	cmp byte [rsi + rcx], '0'
	jb err

	cmp byte [rsi + rcx], '9'
	ja err

get_base:
	mov r10b, byte [rsi + rcx]
	sub r10b, '0'
	imul rax, rax, 10
	add al, r10b

	cmp rax, 36 ;max base
	ja err

	inc rcx
	cmp byte [rsi + rcx], 0
	jne isbase

	cmp rax, 2 ;min base
	jb err

	mov r8, rax
	xor rax, rax
	xor rcx, rcx
	xor r10, r10

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
	mov r9, -1 ;sign

inc_rcx:
	inc rcx

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
	cmp r10b, r8b
	jl make_num

	mov r10b, byte [rdi + rcx]
	sub r10b, 'a'
	add r10b, 10
	cmp r10b, 10
	jl ret
	cmp r10b, r8b
	jl make_num

	jmp ret

make_num:
	imul rax, r8
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
