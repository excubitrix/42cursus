section .text
	global _ft_list_sort

_ft_list_sort:
	cmp rdi, 0				; if (**begin_list == NULL)
	je exit					; 	exit();
	cmp rsi, 0				; if (*cmp == NULL)
	je exit					; 	exit();
	mov	r9, rdi				; r9 = begin_list;
	mov rdx, rsi			; rdx = *cmp;
	mov	r8, rdi				; r8 = prev_list;
	mov rdi, [rdi]			; rdi = list;
	cmp rdi, 0				; if (list == NULL)
	je exit					; 	exit();

loop:
	mov rsi, [rdi + 8]		; rsi = list->next;
	cmp rsi, 0				; if (list_next == NULL)
	je	exit				; 	exit();
	push rdi				;
	push rsi				;
	push rdx				;
	push r8					;
	push r9					;
	mov rdi, [rdi]			; rdi = list->data;
	mov rsi, [rsi]			; rsi = list_next->data;
	call rdx				; rax = cmp(rdi, rsi);
	pop r9					;
	pop r8					;
	pop rdx					;
	pop rsi					;
	pop rdi					; if (rax < 0)
	js iterate				; 	iterate();
	cmp rax, 0				; if (rax == 0)
	je iterate				; 	iterate();
; SWAP
	mov	r10, [rsi + 8]		; tmp = list_next->next;
	mov [rdi + 8], r10		; list->next = tmp;
	mov [rsi + 8], rdi		; list_next->next = list;
	cmp r8, r9				; if prev_list == begin_list;
	je update_head			;
	mov [r8 + 8], rsi		; if not ==> prev_list->next = list->next;
	jmp skip				;
update_head:				;
	mov [r9], rsi			; if so  ==> *begin_list = list->next;
skip:						;
	mov r8, r9				; r8 = prev_list;
	mov rdi, [r9]			; rdi = list;
	jmp loop				;

iterate:
	mov r8, rdi				; prev_list = list;
	mov rdi, [rdi + 8]		; list = list->next;
	jmp	loop				;

exit:
	ret						;
