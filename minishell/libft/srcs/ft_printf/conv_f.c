/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:42:39 by floogman          #+#    #+#             */
/*   Updated: 2020/03/21 17:11:54 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	display_f(t_tab *tab, char *tmp, char prefix)
{
	int		len;
	char	*ptr;

	ptr = tmp;
	if (ft_strcmp(tmp, "0") != 0 && ft_strncmp(tmp, "0.", 2) != 0)
		while (tmp && *tmp == '0')
			tmp++;
	(tab->spec == 'g' && tab->prec > 0 && !tab->flag[4] &&
			(tmp = trim_zeros(tmp, ft_strlen(tmp))));
	len = (prefix) ? ft_strlen(tmp) + 1 : ft_strlen(tmp);
	(prefix && tab->flag[3]) && (write(1, &prefix, 1));
	(!tab->flag[0]) && (pre_padding(tab, len));
	(prefix && !tab->flag[3]) && (write(1, &prefix, 1));
	ft_putstr(tmp);
	free(ptr);
	tab->len += len;
	(tab->flag[0]) && (padding(tab, ' ', tab->width - len, 1));
}

static int	do_f(t_tab *tab, long double f, int len, char prefix)
{
	uintmax_t	i;
	char		*tmp;
	int			prec;

	prec = tab->prec;
	i = prec + len;
	(tab->prec > 0 || tab->flag[4]) && (i++);
	if (!(tmp = (char *)ft_calloc(sizeof(char), (i + 1))))
		return (0);
	while (tab->prec && prec--)
	{
		tmp[--i] = (uintmax_t)f % 10 + 48;
		f /= 10;
	}
	((tab->prec > 0 && len) || tab->flag[4]) && (tmp[--i] = '.');
	while (len--)
	{
		tmp[--i] = (uintmax_t)f % 10 + 48;
		f /= 10;
	}
	display_f(tab, tmp, prefix);
	return (1);
}

int			conv_f(t_tab *tab)
{
	uintmax_t	i;
	long double	f;
	int			tens;
	char		prefix;

	f = (tab->spec == 'g') ? (tab->g) : (long double)(va_arg(tab->ap, double));
	prefix = get_sign(tab, (f < 0) ? 1 : 0);
	f = (f < -0) ? (-f) : (f);
	(tab->prec == -1) && (tab->prec = 6);
	(tab->spec == 'g') && (tab->prec -= get_len((int)(f)));
	tens = (f + 0.5 < 1) ? (1) : (get_len((int)(f + 0.5)));
	i = 0;
	while (i < (uintmax_t)tab->prec)
		f *= (++i) ? (10) : (10);
	f += 0.5;
	if (!(do_f(tab, f, tens, prefix)))
		return (0);
	return (1);
}
