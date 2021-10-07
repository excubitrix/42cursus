section .text
	global _ft_atoi_base

_ft_atoi_base:
	push rdi					;
	push rsi					;
	mov rdi, rsi				; rdi = base;
	call _check_base			; len_base = _check_base(rdi);
	pop rsi						;
	pop rdi						;
	xor r8d, r8d				; nbr = 0;
	mov r9, 1					; sign = 1;
	cmp rax, 2					; if (len_base < 2)
	jl exit						; 	exit();
	mov r10, rax				; r10 = len_base;
	mov rcx, -1					; i = -1;
	xor edx, edx				; rdx = 0;
skip_space:
	inc rcx						; i++;
	mov dl, byte [rdi + rcx]	; dl = str[i];
	cmp dl, 9					; if (str[0] == '\t')
	je skip_space				; 	continue
	cmp dl, 10					; if (str[0] == '\n')
	je skip_space				; 	continue
	cmp dl, 11					; if (str[0] == '\r')
	je skip_space				; 	continue
	cmp dl, 12					; if (str[0] == '\v')
	je skip_space				; 	continue
	cmp dl, 13					; if (str[0] == '\f')
	je skip_space				; 	continue
	cmp dl, 32					; if (str[0] == ' ')
	je skip_space				; 	continue
	dec rcx						; i--;
skip_sign:
	inc rcx						; i++;
	mov	dl, byte [rdi + rcx]	; dl = str[i];
	cmp dl, 43					; if (str[0] == '+')
	je skip_sign				; 	continue
	cmp dl, 45					; if (str[0] == '-')
	je sign						; 	sign();
conv:
	mov dl, byte [rdi + rcx]	; dl = str[i];
	push rdi					;
	push rsi					;
	movzx rdi, dl				; rdi = dl;
	call _get_index				; index = _get_index(rdi, rsi);
	pop rsi						;
	pop rdi						;
	cmp rax, 0					; if (index < 0)
	jl exit						; 	exit();
	imul r8, r10				; nbr *= len_base;
	add r8, rax					; nbr += index;
	inc rcx						; i++;
	jmp conv					;

sign:
	imul r9, -1					; sign *= -1;
	jmp skip_sign				;
	
exit:
	imul r8, r9					; nbr *= sign;
	mov rax, r8					;
	ret							; return (nbr);

_get_index:
	mov rax, -1					; i = -1;
loop:
	inc rax						; i++;
	mov dl, byte [rsi + rax]	; dl = base[i];
	cmp dl, 0					; if (base[i] == '\0')
	je no_match					; 	no_match();
	cmp dl, dil					; if (c != str[i])
	jne loop					; 	continue
	ret							; return (i);
no_match:
	mov rax, -1					; return (-1);
	ret							;

_check_base:
	xor eax, eax				; ret = 0;
	cdq							; | clears rdx when rax is 0
	xor r8d, r8d				; r8 = 0;
	mov rcx, -1					; i = -1;
outer_loop:
	inc rcx						; i++;
	mov dl, byte [rdi + rcx]	; dl = base[i];
	cmp dl, 0					; if (base[i] == '\0')
	je	leave_outer				; 	leave_outer();
	cmp dl, 33					; if (base[i] == '+')
	jl return					; 	return();
	cmp dl, 43					; if (base[i] == '-')
	je return					; 	return();
	cmp dl, 45					; if (base[i] < 33)
	je return					; 	return();
	cmp dl, 127					; if (base[i] > 127)
	jg return					; 	return();
	mov r9, rcx					; j = i;
inner_loop:
	inc r9						; j++;
	mov r8b, byte [rdi + r9]	; r8b = base[j];
	cmp r8b, 0					; if (base[j] == '\0')
	je outer_loop				; 	outer_loop();
	cmp dl, r8b					; if (base[j] == base[i])
	je return					; 	return();
	jmp inner_loop				;
leave_outer:
	mov rax, rcx				; return (i);
return:
	ret							; return (0);