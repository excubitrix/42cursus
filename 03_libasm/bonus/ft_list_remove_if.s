section .text
	global _ft_list_remove_if
    extern _free

_ft_list_remove_if:
	cmp rdi, 0				; if (begin_list == NULL)
	je exit					; 	exit();
	cmp rdx, 0				; if (*cmp == NULL)
	je exit					; 	exit();
	cmp rcx, 0				; if (*free_fct == NULL)
	je exit					; 	exit();
	mov	r9, rdi				; r9 = begin_list;
	mov	r8, rdi				; r8 = prev_list;
	mov rdi, [rdi]			; rdi = list;
loop:
	cmp rdi, 0				; if (list == NULL)
	je exit					; 	exit();
	push rdi				;
	push rsi				;
	push rdx				;
	push rcx				;
	push r8					;
	push r9					;
	mov rdi, [rdi]			; rdi = list->data
	call rdx				; rax = cmp(rdi, rsi);
	pop r9					;
	pop r8					;
	pop rcx					;
	pop rdx					;
	pop rsi					;
	pop rdi					;
	cmp rax, 0				; if (rax == 0)
	je remove				; 	remove();
	mov r8, rdi				; prev_list = list;
	mov rdi, [rdi + 8]		; list = list->next;
	jmp	loop				;

remove:
	push rdi				;
	push rsi				;
	push rdx				;
	push rcx				;
	push r8					;
	push r9					;
	mov rdi, [rdi]			;
	call rcx				; free_fct(list->data);
	pop r9					;
	pop r8					;
	pop rcx					;
	pop rdx					;
	pop rsi					;
	pop rdi					; rdi = list;
	mov	r10, [rdi + 8]		; tmp = list->next;
	cmp r8, r9				; prev_list == begin_list ?
	je update_head			;
	mov [r8 + 8], r10		; if not ==> prev_list->next = tmp;
	jmp skip				;
update_head:				;
	mov [r9], r10			; if so  ==> begin_list = tmp;
skip:						;
	push r10				;
	push rsi				;
	push rdx				;
	push rcx				;
	push r8					;
	push r9					;
	sub rsp, 8				;
	call _free				; free(list);
	add rsp, 8				;
	pop r9					;
	pop r8					;
	pop rcx					;
	pop rdx					;
	pop rsi					;
	pop rdi					;
	jmp loop				;

exit:
	ret						;
