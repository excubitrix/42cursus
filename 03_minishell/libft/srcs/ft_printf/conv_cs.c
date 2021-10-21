/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_cs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:07:13 by floogman          #+#    #+#             */
/*   Updated: 2020/03/21 17:11:39 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			conv_c(t_tab *tab)
{
	wint_t	c;

	if (ft_strcmp(tab->modi, "l") == 0)
	{
		c = (wchar_t)va_arg(tab->ap, wchar_t);
		display_wchar(tab, c);
		return (1);
	}
	else
		c = (wint_t)((char)va_arg(tab->ap, int));
	(!tab->flag[0]) && (pre_padding(tab, 1));
	ft_putchar(c);
	tab->len++;
	(tab->flag[0]) && (padding(tab, ' ', tab->width - 1, 1));
	return (1);
}

static char	*get_s(t_tab *tab, char *s)
{
	if (tab->prec > -1 && s)
		if (!(s = ft_strndup(s, tab->prec)))
			return (NULL);
	if (tab->prec == -1 && s)
		if (!(s = ft_strdup(s)))
			return (NULL);
	if (tab->prec > -1 && !s)
		if (!(s = ft_strndup("(null)", tab->prec)))
			return (NULL);
	if (tab->prec == -1 && !s)
		if (!(s = ft_strdup("(null)")))
			return (NULL);
	return (s);
}

int			conv_s(t_tab *tab)
{
	char	*s;
	int		len;

	s = va_arg(tab->ap, char *);
	if (!(s = get_s(tab, s)))
		return (0);
	len = ft_strlen(s);
	(!tab->flag[0]) && (pre_padding(tab, len));
	ft_putstr(s);
	free(s);
	tab->len += len;
	(tab->flag[0]) && (padding(tab, ' ', tab->width - len, 1));
	return (1);
}
