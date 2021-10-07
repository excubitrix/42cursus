section .text
	global _ft_strlen

_ft_strlen:					; size_t	ft_strlen(const char *s)
	xor eax, eax			; len = 0;

count:
	cmp byte [rdi + rax], 0	; if (s[len] == '\0');
	je	exit				; 	exit();
	inc	rax					; len++;
	jmp	count				;

exit:
	ret						; return(len);
