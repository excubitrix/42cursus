/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_ws.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 09:44:10 by floogman          #+#    #+#             */
/*   Updated: 2020/03/21 17:11:58 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		char_len(wchar_t c)
{
	int len;

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

static wchar_t	*wstrndup(wchar_t *str, size_t n)
{
	wchar_t	*new;
	size_t	i;

	i = 0;
	if (!(new = (wchar_t *)malloc(sizeof(wchar_t) * n + 1)))
		return (NULL);
	while (str[i] && i < n)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static wchar_t	*wstrdup(wchar_t *str)
{
	int		len;

	len = 0;
	while (str[len])
		len++;
	return (wstrndup(str, len));
}

static int		display_null(t_tab *tab)
{
	wchar_t		*s;
	int			i;

	i = 0;
	if (!(s = wstrdup(L"(null)")))
		return (0);
	if (tab->prec > -1)
	{
		while (s[i] && tab->prec-- > 0)
			display_wchar(tab, s[i++]);
	}
	else
	{
		while (s[i])
			display_wchar(tab, s[i++]);
	}
	free(s);
	return (1);
}

int				conv_ws(t_tab *tab)
{
	wchar_t		*s;
	int			i;
	int			j;
	int			len;

	i = 0;
	len = 0;
	if (!(s = (wchar_t *)va_arg(tab->ap, wchar_t *)))
		return (display_null(tab));
	while (s[i] && !(j = 0))
	{
		if (tab->prec > -1 && (len + char_len(s[i])) > tab->prec)
			break ;
		len += char_len(s[i++]);
	}
	(!tab->flag[0]) && (pre_padding(tab, len));
	while (j < i)
		display_wchar(tab, s[j++]);
	(tab->flag[0]) && (padding(tab, ' ', tab->width - len, 1));
	return (1);
}
