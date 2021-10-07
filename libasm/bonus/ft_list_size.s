section .text
	global _ft_list_size

_ft_list_size:
	xor eax, eax		; i = 0

loop:
	cmp rdi, 0			; if (list == NULL)
	je	exit			; 	exit();
	mov rdi, [rdi + 8]	; rdi = list->next;
	inc	rax				; i++;
	jmp	loop			;

exit:
	ret					; return (i);
