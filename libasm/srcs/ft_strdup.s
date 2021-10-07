section .text
	global _ft_strdup
	extern _ft_strlen
	extern _ft_strcpy
	extern _malloc
	extern ___error

_ft_strdup:				; char	*ft_strdup(const char *s)
	cmp rdi, 0			; if (s == NULL)
	je exit				; 	exit();
	push rdi			;
	call _ft_strlen 	; len = ft_strlen(s);
	inc rax				; len++;
	mov rdi, rax		; rdi = len;
	call _malloc		; if (!(new = malloc(len)))
	pop rsi				;	err(); | checks CF (carry flag)
	jc err				; rsi = s;
	mov rdi, rax		; rdi = new;
	call _ft_strcpy		; new = ft_strcpy(rdi, rsi);
exit:
	ret					; return(new);

err:
	push rax			;
	call ___error		; ptr = ___error();
	pop rdi				; rdi = errno;
	mov [rax], rdi		; *ptr = errno;
	xor eax, eax		; new = NULL;
	jmp exit			; exit();
