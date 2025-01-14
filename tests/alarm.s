global _start
global handler

handler:
	ret

_start:
	mov	rcx, rsp
	sub	rsp, 48
	lea	rdx, [handler]
	mov	[rcx + 0], rdx
	mov	QWORD [rcx + 8],	0
	mov	QWORD [rcx + 16],	0
	mov	QWORD [rcx + 24],	0
	mov	QWORD [rcx + 32],	0

	mov	rax, 13			; sigaction
	mov	rdi, 14			; SIGALRM
	mov	rsi, rcx
	mov	rdx, 0
	mov	r10, 8
	syscall

	mov	rax, 37		; alarm
	mov	rdi, 1
	syscall

	mov	rax, 34		; pause
	syscall

	mov	rax, 60		; exit
	mov	rdi, 0
	syscall
