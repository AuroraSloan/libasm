BITS 64

section .note.GNU-stack

section .data
num dq 0
sign db 1

section .text
global ft_atoi_base

ft_atoi_base:
	xor rcx, rcx

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
	je pos

	cmp byte [rdi + rcx], '-'
	je neg 

	jmp check_char

pos:
	inc rcx
	jmp check_char

neg:
	mov byte [rel sign], -1
	inc rcx

check_char:
	cmp byte [rdi + rcx], '0'
	jb ret
	cmp byte [rdi + rcx], '9'
	jna make_num


	cmp byte [rdi + rcx], 'A'
	jb ret
	cmp byte [rdi + rcx], 'Z'
	jna make_num

	cmp byte [rdi + rcx], 'a'
	jb ret
	cmp byte [rdi + rcx], 'z'
	jna make_num

	jmp ret

make_num:
	xor rdx, rdx
	mov dl, byte [rdi + rcx]
	sub rdx, '0'

	xor rax, rax
	mov rax, qword [rel num]
	imul rsi
	mov qword [rel num], rax
	add qword [rel num], rdx

	cmp qword [rel num], 0
	jl err

	inc rcx
	cmp byte [rdi + rcx], 0
	je ret
	jmp check_char

ret:
	xor rax, rax
	mov rax, qword [rel num]
	imul byte [rel sign]
	ret

err:
	xor rax, rax
	add byte [rel sign], 1
	mov al, byte [rel sign]
	xor rdx, rdx
	mov rbx, -2
	idiv rbx
