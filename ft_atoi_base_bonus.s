BITS 64

section .note.GNU-stack

section .text
global ft_atoi_base

ft_atoi_base:
	test rdi, rdi
	je err
	test rsi, rsi
	je err

	xor rcx, rcx ;i
	xor rax, rax ;num
	xor r8, r8 ;base
	mov r9, 1 ;sign
	xor r10, r10 ;tmp
	xor r11, r11 ;base i

	cmp byte [rsi + r8], 0
	je err

check_base_char:
	cmp byte [rsi + r8], '+'
	je err
	cmp byte [rsi + r8], '-'
	je err
	cmp byte [rsi + r8], 0x09
	je err
	cmp byte [rsi + r8], 0x0A
	je err
	cmp byte [rsi + r8], ' '
	je err

check_base_double_char:
	cmp r8, rcx
	je get_next_base_char
	mov r10b, byte [rsi + rcx]
	cmp byte [rsi + r8], r10b
	je err
	inc rcx
	jmp check_base_double_char

get_next_base_char:
	inc r8
	cmp byte [rsi + r8], 0
	je is_valid_base
	xor rcx, rcx
	jmp check_base_char

is_valid_base:
	cmp r8, 2
	jl err
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
	imul r9, -1 ;sign

inc_rcx:
	inc rcx
	jmp check_sign

check_char:
	cmp byte [rdi + rcx], 0
	je ret
	xor r11, r11

get_digit_index:
	xor r10, r10
	mov r10b, byte [rsi + r11]
	cmp r10, 0
	je ret
	cmp byte [rdi + rcx], r10b
	je make_num
	inc r11
	jmp get_digit_index

make_num:
	imul rax, r8
	add rax, r11

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
