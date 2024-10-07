BITS 64

section .data
	odds db "odd", 0xa
	ol equ $ - odds
	evns db "even", 0xa
	el equ $ - evns

section .text
global _start

_start:
	;mov rax, 10
	mov rax, 11
	test rax, 1
	jz evn 

	mov rax, 1
	mov rdi, 1
	mov rsi, odds
	mov rdx, ol
	syscall
	jmp end

evn:	
	mov rax, 1
	mov rdi, 1
	mov rsi, evns
	mov rdx, el
	syscall

end:
	mov rax, 60
	mov rdi, 0
	syscall
