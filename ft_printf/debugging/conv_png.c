/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_png.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:27:21 by floogman          #+#    #+#             */
/*   Updated: 2021/10/04 18:44:28 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	conv_p(t_tab *tab)
{
	void		*p;
	char		*s;
	int			s_len;
	int			len;

	p = va_arg(tab->ap, void *);
	s = ft_itoa_base((uintmax_t)p, "0123456789abcdef", 16);
	if (!s)
		return (FAILURE);
	if (tab->prec == 0 && p == 0)
		*s = '\0';
	s_len = ft_strlen(s);
	len = s_len + 2;
	if (len <= tab->width)
		tab->len += tab->width;
	else
		tab->len += len;
	if (tab->width < tab->prec)
		tab->len += tab->prec - s_len;
	display_nbr(tab, s, "0x", len);
	return (SUCCESS);
}

int	conv_n(t_tab *tab)
{
	if (!ft_strncmp(tab->modi, "hh", 3))
		*((char *)va_arg(tab->ap, int *)) = tab->len;
	else if (!ft_strncmp(tab->modi, "h", 2))
		*((short *)va_arg(tab->ap, int *)) = tab->len;
	else if (!ft_strncmp(tab->modi, "ll", 3))
		*va_arg(tab->ap, long long *) = tab->len;
	else if (!ft_strncmp(tab->modi, "l", 2))
		*(va_arg(tab->ap, long *)) = tab->len;
	else
		*(va_arg(tab->ap, int *)) = tab->len;
	return (SUCCESS);
}

static int	get_tens_g(t_tab *tab, int *tens, long double g, long double rnd)
{
	int		prec;
	int		i;

	prec = tab->prec;
	if (g < 1)
	{
		while (g && g < 1)
		{
			if (--(*tens))
				g *= 10;
			if (!((long)g % 10))
				tab->prec++;
		}
	}
	else
	{
		i = 0;
		while (i++ < tab->prec)
			rnd /= 10;
		while (g + rnd >= 1)
			if (++(*tens))
				g /= 10;
	}
	return (prec);
}

int	conv_g(t_tab *tab)
{
	long double	g_cpy;
	int			tens;
	int			prec;

	tab->g = (long double)va_arg(tab->ap, double);
	g_cpy = (long double)tab->g;
	if (tab->g < 0)
		g_cpy = -g_cpy;
	if (tab->prec == -1)
		tab->prec = 6;
	if ((!g_cpy && !tab->flag[4]) || !tab->prec)
		tab->prec = 1;
	tens = 0;
	prec = get_tens_g(tab, &tens, g_cpy, 0.5);
	if ((tens < -4) || ((tens - 1) >= tab->prec))
		tab->prec = prec - 1;
	if ((tens < -4) || ((tens - 1) >= tab->prec))
		conv_e(tab);
	else
		conv_f(tab);
	return (SUCCESS);
}
