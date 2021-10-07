section .text
	global _ft_read
	extern ___error

_ft_read:				; ssize_t	ft_read(int fd, void *buf, size_t count)
	mov rax, 0x2000003	;
	syscall				; if (!(ret = read(fd, buf, count)))
	jc err				; 	err(); | checks CF (carry flag)
exit:
	ret					; return(ret);

err:
	push rax			;
	call ___error		; ptr = ___error();
	pop rdi				; rdi = errno;
	mov [rax], rdi		; *ptr = errno;
	mov rax, -1			; ret = -1;
	jmp exit			; exit();
