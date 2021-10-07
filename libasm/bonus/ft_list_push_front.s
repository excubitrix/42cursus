section .text
	global _ft_list_push_front
	extern _malloc

_ft_list_push_front:
	cmp rdi, 0				; if (begin_list == NULL)
	je exit					; 	exit();
	push rdi				;
	push rsi				;
	mov edi, 16				; rdi = sizeof(list);
	sub rsp, 8				;
	call _malloc			; new_list = malloc(rdi);
	add rsp, 8				;
	pop rsi					;
	pop rdi					;
	cmp rax, 0				; if (new_list == NULL)
	je exit					; 	exit();
	mov [rax], rsi			; new_list->data = data;
	mov rsi, [rdi]			; rsi = *begin_list;
	mov [rax + 8], rsi		; new_list->next = rsi;
	mov [rdi], rax			; *begin_list = new_list;
exit:
	ret						;
