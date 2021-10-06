/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_di.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 10:45:59 by floogman          #+#    #+#             */
/*   Updated: 2020/03/21 17:11:43 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t	get_nbr(t_tab *tab)
{
	intmax_t	nbr;

	if (ft_strcmp(tab->modi, "hh") == 0)
		nbr = (intmax_t)((char)(va_arg(tab->ap, int)));
	else if (ft_strcmp(tab->modi, "h") == 0)
		nbr = (intmax_t)((short)(va_arg(tab->ap, int)));
	else if (ft_strcmp(tab->modi, "ll") == 0)
		nbr = (intmax_t)(va_arg(tab->ap, long long));
	else if (ft_strcmp(tab->modi, "l") == 0)
		nbr = (intmax_t)(va_arg(tab->ap, long));
	else
		nbr = (intmax_t)(va_arg(tab->ap, int));
	return (nbr);
}

static int		display_d(t_tab *tab, intmax_t n, char prefix)
{
	int		len;
	int		n_len;
	char	*nbr;

	n *= (n < 0) ? -1 : 1;
	n_len = get_len(n);
	len = n_len;
	(n_len <= tab->prec && tab->prec >= 0) && (len = tab->prec);
	prefix && len++;
	tab->len += (len <= tab->width) ? tab->width : len;
	(!tab->flag[0]) && (padding(tab, ' ', tab->width - len, 0));
	(prefix) && (ft_putchar(prefix));
	padding(tab, '0', tab->prec - n_len, 0);
	if (!(ft_putstr(nbr = ft_itoa_base(n, "0123456789", 10))))
		return (0);
	free(nbr);
	(tab->flag[0]) && (padding(tab, ' ', tab->width - len, 0));
	return (1);
}

int				conv_d(t_tab *tab)
{
	intmax_t	n;

	n = get_nbr(tab);
	if (n == 0 && tab->prec == 0)
	{
		if (tab->flag[1] || tab->flag[2])
		{
			(!tab->flag[0]) && (pre_padding(tab, 1));
			ft_putchar(tab->flag[1] ? '+' : ' ');
			tab->len++;
			(tab->flag[0]) && (padding(tab, ' ', tab->width - 1, 1));
		}
		else
			padding(tab, ' ', tab->width, 1);
		return (1);
	}
	if (tab->flag[3] && tab->prec == -1 && !tab->flag[0])
	{
		tab->prec = tab->width;
		if (n < 0 || tab->flag[2] || tab->flag[1] || tab->flag[0])
			tab->prec--;
	}
	if (!(display_d(tab, n, get_sign(tab, (n < 0) ? 1 : 0))))
		return (0);
	return (1);
}
