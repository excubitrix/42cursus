/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_cs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:07:13 by floogman          #+#    #+#             */
/*   Updated: 2021/10/04 19:34:05 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	conv_c(t_tab *tab)
{
	wint_t	c;

	if (!ft_strncmp(tab->modi, "l", 2))
	{
		c = (wchar_t)va_arg(tab->ap, wchar_t);
		display_wchar(tab, c);
		return (SUCCESS);
	}
	else
		c = (wint_t)((char)va_arg(tab->ap, int));
	if (!tab->flag[0])
		pre_padding(tab, 1);
	write(1, &c, 1);
	tab->len++;
	if (tab->flag[0])
		padding(tab, ' ', tab->width - 1, 1);
	return (SUCCESS);
}

void	display_s(t_tab *tab, char *s, int len)
{
	if (!tab->flag[0])
		pre_padding(tab, len);
	write(1, s, len);
	tab->len += len;
	if (tab->flag[0])
		padding(tab, ' ', tab->width - len, 1);
	free(s);
}

int	conv_s(t_tab *tab)
{
	char	*s;

	if (!ft_strncmp(tab->modi, "l", 2))
		return (conv_ws(tab));
	s = va_arg(tab->ap, char *);
	if (tab->prec > -1 && s)
		s = ft_strndup(s, tab->prec);
	else if (tab->prec == -1 && s)
		s = ft_strdup(s);
	else if (tab->prec > -1 && !s)
		s = ft_strndup("(null)", tab->prec);
	else if (tab->prec == -1 && !s)
		s = ft_strdup("(null)");
	if (!s)
		return (FAILURE);
	display_s(tab, s, ft_strlen(s));
	return (SUCCESS);
}
