section .text
	global _ft_write
	extern ___error

_ft_write:				; ssize_t	ft_write(int fd, const void *buf, size_t count)
	mov rax, 0x2000004	;
	syscall				; if (!(ret = write(fd, buf, count)))
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
