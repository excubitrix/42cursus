/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_ux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:44:43 by floogman          #+#    #+#             */
/*   Updated: 2020/03/21 17:11:56 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static uintmax_t	get_nbr(t_tab *tab)
{
	uintmax_t	nbr;

	if (ft_strcmp(tab->modi, "hh") == 0)
		nbr = (uintmax_t)((unsigned char)(va_arg(tab->ap, int)));
	else if (ft_strcmp(tab->modi, "h") == 0)
		nbr = (uintmax_t)((unsigned short)(va_arg(tab->ap, int)));
	else if (ft_strcmp(tab->modi, "ll") == 0)
		nbr = (uintmax_t)(va_arg(tab->ap, unsigned long long));
	else if (ft_strcmp(tab->modi, "l") == 0)
		nbr = (uintmax_t)(va_arg(tab->ap, unsigned long));
	else
		nbr = (uintmax_t)(va_arg(tab->ap, unsigned int));
	return (nbr);
}

int					conv_u(t_tab *tab)
{
	uintmax_t	u;
	int			len;
	int			u_len;
	char		*nbr;

	u = get_nbr(tab);
	if (u == 0 && tab->prec == 0)
	{
		padding(tab, ' ', tab->width, 1);
		return (1);
	}
	(tab->flag[3] == '0' && tab->prec == -1 && !tab->flag[0]) &&
			(tab->prec = tab->width);
	u_len = get_len(u);
	len = (u_len <= tab->prec) ? tab->prec : u_len;
	tab->len += (len <= tab->width) ? tab->width : len;
	(!tab->flag[0]) && (padding(tab, ' ', tab->width - len, 0));
	padding(tab, '0', tab->prec - u_len, 0);
	if (!(ft_putstr(nbr = ft_itoa_base(u, "0123456789", 10))))
		return (0);
	free(nbr);
	(tab->flag[0]) && (padding(tab, ' ', tab->width - len, 0));
	return (1);
}

static void			display_x(t_tab *tab, uintmax_t x, char *s)
{
	int		len;
	int		x_len;

	x_len = ft_strlen(s);
	if (x_len && tab->flag[4] && x && tab->flag[3] && tab->width
						&& !tab->flag[0])
		x_len += 2;
	else if (x_len && tab->flag[4] && x)
	{
		tab->width -= 2;
		tab->len += 2;
	}
	len = (x_len <= tab->prec && tab->prec > 0) ? tab->prec : x_len;
	tab->len += (len <= tab->width) ? tab->width : len;
	(!tab->flag[0]) && (padding(tab, ' ', tab->width - len, 0));
	(x && tab->flag[4] && tab->spec == 'x') && (ft_putstr("0x"));
	(x && tab->flag[4] && tab->spec == 'X') && (ft_putstr("0X"));
	padding(tab, '0', tab->prec - x_len, 0);
	ft_putstr(s);
	free(s);
	(tab->flag[0]) && (padding(tab, ' ', tab->width - len, 0));
}

int					conv_x(t_tab *tab)
{
	uintmax_t	x;
	char		*s;

	x = get_nbr(tab);
	if (x == 0 && tab->prec == 0)
	{
		padding(tab, ' ', tab->width, 1);
		return (1);
	}
	if (!(s = ft_itoa_base(x, tab->spec == 'x' ? "0123456789abcdef" :
			"0123456789ABCDEF", 16)))
		return (0);
	if (tab->flag[3] && tab->prec == -1 && !tab->flag[0])
		tab->prec = tab->width;
	else if (tab->flag[3] && tab->flag[4] && tab->prec > 0 &&
			!tab->flag[0] && x)
		tab->prec += 2;
	display_x(tab, x, s);
	return (1);
}
