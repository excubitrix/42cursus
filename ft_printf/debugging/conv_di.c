/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_di.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 10:45:59 by floogman          #+#    #+#             */
/*   Updated: 2021/10/05 08:42:41 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t	get_nbr(t_tab *tab)
{
	intmax_t	nbr;

	if (!ft_strncmp(tab->modi, "hh", 3))
		nbr = (intmax_t)((char)va_arg(tab->ap, int));
	else if (!ft_strncmp(tab->modi, "h", 2))
		nbr = (intmax_t)((short)va_arg(tab->ap, int));
	else if (!ft_strncmp(tab->modi, "ll", 3))
		nbr = (intmax_t)va_arg(tab->ap, long long);
	else if (!ft_strncmp(tab->modi, "l", 2))
		nbr = (intmax_t)va_arg(tab->ap, long);
	else
		nbr = (intmax_t)va_arg(tab->ap, int);
	return (nbr);
}

static int	display_d(t_tab *tab, intmax_t n, char *prefix)
{
	int		len;
	int		n_len;
	char	*nbr;

	if (n < 0)
		n = -n;
	nbr = ft_itoa_base(n, "0123456789", 10);
	if (!nbr)
		return (FAILURE);
	n_len = ft_strlen(nbr);
	len = get_len(tab, n_len, prefix);
	display_nbr(tab, nbr, prefix, len);
	return (SUCCESS);
}

static void	display_signed(t_tab *tab, char *sign)
{
	if (!tab->flag[0])
		pre_padding(tab, 1);
	write(1, sign, 1);
	tab->len++;
	if (tab->flag[0])
		padding(tab, ' ', tab->width - 1, 1);
}

int	conv_d(t_tab *tab)
{
	intmax_t	n;

	n = get_nbr(tab);
	if (!n && !tab->prec)
	{
		if (tab->flag[1] || tab->flag[2])
			display_signed(tab, get_sign(tab, n < 0));
		else
			padding(tab, ' ', tab->width, 1);
		return (SUCCESS);
	}
	if (tab->flag[3] && tab->prec == -1 && !tab->flag[0])
	{
		tab->prec = tab->width;
		if (n < 0 || tab->flag[2] || tab->flag[1] || tab->flag[0])
			tab->prec--;
	}
	if (display_d(tab, n, get_sign(tab, n < 0)) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
