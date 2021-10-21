section .text
	global _ft_strcmp

_ft_strcmp:
	xor ecx, ecx				; i = 0;
	xor eax, eax				; rax = 0;
	cdq							; rdx = 0; | clears rdx when rax is 0

comp:
	mov al, byte [rdi + rcx]	; rax = s1[i];
	mov dl, byte [rsi + rcx]	; rdx = s2[i];
	cmp al, 0					; if (s1[i] == 0)
	je	exit					; 	exit();
	cmp al, dl					; if (a != b)
	jne	exit					; 	exit();
	inc	rcx						; i++;
	jmp	comp					;

exit:
	sub rax, rdx				; rax -= rdx;
	ret							; return(rax);
