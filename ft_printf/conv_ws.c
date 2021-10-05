/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_ws.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 09:44:10 by floogman          #+#    #+#             */
/*   Updated: 2021/10/05 08:44:52 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	char_len(wchar_t c)
{
	int	len;

	if (c <= 127)
		len = 1;
	else if (c > 127 && c <= 2047)
		len = 2;
	else if (c > 2048 && c <= 65535)
		len = 3;
	else
		len = 4;
	return (len);
}

static wchar_t	*wstrdup(wchar_t *str)
{
	wchar_t	*new;
	size_t	n;
	size_t	i;

	n = 0;
	while (str[n])
		n++;
	new = malloc((n + 1) * sizeof(wchar_t));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static int	display_null(t_tab *tab)
{
	wchar_t		*s;
	int			i;

	i = 0;
	s = wstrdup(L"(null)");
	if (!s)
		return (FAILURE);
	if (tab->prec > -1)
		while (s[i] && tab->prec-- > 0)
			display_wchar(tab, s[i++]);
	else
		while (s[i])
			display_wchar(tab, s[i++]);
	free(s);
	return (SUCCESS);
}

int	conv_ws(t_tab *tab)
{
	wchar_t		*s;
	int			i;
	int			j;
	int			len;

	s = (wchar_t *)va_arg(tab->ap, wchar_t *);
	if (!s)
		return (display_null(tab));
	i = 0;
	len = 0;
	while (s[i])
	{
		if (tab->prec >= 0 && (len + char_len(s[i])) > tab->prec)
			break ;
		len += char_len(s[i++]);
	}
	if (!tab->flag[0])
		pre_padding(tab, len);
	j = 0;
	while (j < i)
		display_wchar(tab, s[j++]);
	if (tab->flag[0])
		padding(tab, ' ', tab->width - len, 1);
	return (SUCCESS);
}
