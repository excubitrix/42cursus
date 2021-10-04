/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_ux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:44:43 by floogman          #+#    #+#             */
/*   Updated: 2021/10/04 11:39:44 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static uintmax_t	get_nbr(t_tab *tab)
{
	uintmax_t	nbr;

	if (!ft_strncmp(tab->modi, "hh", 3))
		nbr = (uintmax_t)((unsigned char)(va_arg(tab->ap, int)));
	else if (!ft_strncmp(tab->modi, "h", 2))
		nbr = (uintmax_t)((unsigned short)(va_arg(tab->ap, int)));
	else if (!ft_strncmp(tab->modi, "ll", 3))
		nbr = (uintmax_t)(va_arg(tab->ap, unsigned long long));
	else if (!ft_strncmp(tab->modi, "l", 2))
		nbr = (uintmax_t)(va_arg(tab->ap, unsigned long));
	else
		nbr = (uintmax_t)(va_arg(tab->ap, unsigned int));
	return (nbr);
}

int	conv_u(t_tab *tab)
{
	uintmax_t	u;
	int			len;
	int			n_len;
	char		*nbr;

	u = get_nbr(tab);
	if (!u && !tab->prec)
	{
		padding(tab, ' ', tab->width, 1);
		return (SUCCESS);
	}
	if (tab->flag[3] && tab->prec == -1 && !tab->flag[0])
		tab->prec = tab->width;
	nbr = ft_itoa_base(u, "0123456789", 10);
	if (!nbr)
		return (FAILURE);
	n_len = ft_strlen(nbr);
	len = get_len(tab, n_len, 0);
	display_nbr(tab, nbr, NULL, len);
	return (SUCCESS);
}

static void	display_x(t_tab *tab, uintmax_t x, char *s)
{
	int		len;
	int		x_len;
	char	*prefix;

	x_len = ft_strlen(s);
	if (x && x_len && tab->flag[4] && tab->flag[3]
		&& tab->width && !tab->flag[0])
		x_len += 2;
	else if (x && x_len && tab->flag[4])
	{
		tab->width -= 2;
		tab->len += 2;
	}
	len = get_len(tab, x_len, 0);
	prefix = NULL;
	if (x && tab->flag[4] && tab->spec == 'x')
		prefix = "0x";
	else if (x && tab->flag[4] && tab->spec == 'X')
		prefix = "0X";
	display_nbr(tab, s, prefix, len);
}

int	conv_x(t_tab *tab)
{
	uintmax_t	x;
	char		*s;

	x = get_nbr(tab);
	if (!x && !tab->prec)
	{
		padding(tab, ' ', tab->width, 1);
		return (SUCCESS);
	}
	if (tab->spec == 'x')
		s = ft_itoa_base(x, "0123456789abcdef", 16);
	else
		s = ft_itoa_base(x, "0123456789ABCDEF", 16);
	if (!s)
		return (FAILURE);
	if (tab->flag[3] && tab->prec == -1 && !tab->flag[0])
		tab->prec = tab->width;
	else if (x && tab->flag[3] && tab->flag[4]
		&& tab->prec > 0 && !tab->flag[0])
		tab->prec += 2;
	display_x(tab, x, s);
	return (SUCCESS);
}
