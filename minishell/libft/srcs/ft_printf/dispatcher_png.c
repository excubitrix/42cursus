/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher_png.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:27:21 by floogman          #+#    #+#             */
/*   Updated: 2020/03/21 17:12:00 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		dispatcher(t_tab *tab)
{
	int	res;

	res = 1;
	(tab->spec == 'c') && (res = conv_c(tab));
	((tab->spec == 's') && (ft_strcmp(tab->modi, "l"))) &&
			(res = conv_s(tab));
	((tab->spec == 's') && (!ft_strcmp(tab->modi, "l"))) &&
			(res = conv_ws(tab));
	((tab->spec == 'd' || tab->spec == 'i')) && (res = conv_d(tab));
	(tab->spec == 'p') && (res = conv_p(tab));
	(tab->spec == 'u') && (res = conv_u(tab));
	((tab->spec == 'x' || tab->spec == 'X')) && (res = conv_x(tab));
	(tab->spec == '%') && (res = display_mod(tab));
	(tab->spec == 'n') && (res = conv_n(tab));
	(tab->spec == 'f') && (res = conv_f(tab));
	(tab->spec == 'g') && (res = conv_g(tab));
	(tab->spec == 'e') && (res = conv_e(tab));
	return (res);
}

int		conv_p(t_tab *tab)
{
	void		*p;
	char		*s;
	int			len;

	p = va_arg(tab->ap, void *);
	if (!(s = ft_itoa_base((uintmax_t)p, "0123456789abcdef", 16)))
		return (0);
	(tab->prec == 0 && p == 0) && (*s = '\0');
	len = ft_strlen(s) + 2;
	tab->len += (len <= tab->width) ? tab->width : len;
	(tab->width < tab->prec) && (tab->len += (tab->prec - len) + 2);
	(!tab->flag[0]) && (padding(tab, ' ', tab->width - len, 0));
	ft_putstr("0x");
	padding(tab, '0', (tab->prec - len) + 2, 0);
	ft_putstr(s);
	free(s);
	(tab->flag[0]) && (padding(tab, ' ', tab->width - len, 0));
	return (1);
}

int		display_mod(t_tab *tab)
{
	(!tab->flag[0]) && (pre_padding(tab, 1));
	write(1, "%", 1);
	tab->len++;
	(tab->flag[0]) && (padding(tab, ' ', tab->width - 1, 1));
	return (1);
}

int		conv_n(t_tab *tab)
{
	if (ft_strcmp(tab->modi, "hh") == 0)
		*(va_arg(tab->ap, int *)) = (char)tab->len;
	else if (ft_strcmp(tab->modi, "h") == 0)
		*(va_arg(tab->ap, int *)) = (short)tab->len;
	else if (ft_strcmp(tab->modi, "ll") == 0)
		*(va_arg(tab->ap, long long *)) = (long long)tab->len;
	else if (ft_strcmp(tab->modi, "l") == 0)
		*(va_arg(tab->ap, long *)) = (long)tab->len;
	else
		*(va_arg(tab->ap, int *)) = tab->len;
	return (1);
}

int		conv_g(t_tab *tab)
{
	int			i;
	int			tens;
	long double	rnd;
	long double g_cpy;

	i = 0;
	tens = 0;
	tab->g = (long double)va_arg(tab->ap, double);
	g_cpy = (long double)tab->g;
	(tab->g < -0) && (g_cpy *= -1);
	(tab->prec == -1) && (tab->prec = 6);
	(g_cpy == 0 || tab->prec == 0) && (tab->prec = 1);
	rnd = 0.5;
	while (i < tab->prec)
		rnd /= (i++) ? 10 : 10;
	if (g_cpy < 1)
		while (g_cpy && g_cpy < 1)
			g_cpy *= (tens--) ? (10) : (10);
	else
		while (g_cpy + rnd > 1)
			g_cpy /= (tens++) ? (10) : (10);
	((tens < -4) || ((tens - 1) >= tab->prec)) ? conv_e(tab) :
			conv_f(tab);
	return (1);
}
