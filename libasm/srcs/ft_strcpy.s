section .text
	global _ft_strcpy
	extern _ft_strlen

_ft_strcpy:				; char	*ft_strcpy(char *dest, const char *src)
	cmp rsi, 0			; if (src == NULL)
	je exit				; 	exit();
	push rdi			;
	push rsi			;
	mov rdi, rsi		; rdi = src;
	call _ft_strlen 	; len = ft_strlen(rdi);
	pop rsi				;
	pop rdi				;
	mov rcx, rax		; rcx = len;
	cld					; | sets DF (direction flag) to 0 for forward (as opposed to std which sets it to 1 for backward)
	mov rax, rdi		; rax = dest;
	rep movsb			; while (count--) | rep repeats the following instruction rcx times (decrementing rcx until it is 0)
						;	*dest++ = *scr++; | movsb (the instruction) moves *rsi to *rdi and increments both registries (pointers) according to the DF (in this case forward)
	mov byte [rdi], 0	; *dest = '\0';
	ret					; return(dest);

exit:
	mov rax, rdi		;
	ret					; return(dest);
