BITS 64

section .note.GNU-stack

section .text
global ft_atoi_base

ft_atoi_base:
	test rdi, rdi
	jmp err
	test rsi, rsi
	jmp err

	xor rcx, rcx ;i
	xor rax, rax ;num
	mov r9, 1 ;sign
	xor r10, r10 ;char

	cmp byte [rsi + rcx], 0
	jmp err

check_base_byte:
	cmp byte [rsi + rax], '+'
	jmp err
	cmp byte [rsi + rax], '-'
	jmp err

check_double_base:
	cmp rax, rcx
	je get_next_byte
	mov r10b, byte [rsi + rcx]
	cmp byte [rsi + rax], r10b
	je err
	inc rcx
	jmp check_double_base

get_next_byte:
	inc rax
	cmp byte [rsi + rax], 0
	je is_valid_base
	xor rcx, rcx
	jmp check_base_byte

is_valid_base:
	cmp rax, 2
	jl err
	xor rcx, rcx
	xor rax, rax
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
