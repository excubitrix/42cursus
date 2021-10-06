/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_e.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:20:44 by floogman          #+#    #+#             */
/*   Updated: 2020/03/21 17:11:49 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*generate_suffix(int tens)
{
	long	tmpn;
	int		len;
	char	*str;

	tmpn = tens < 0 ? -tens : tens;
	len = get_len(tmpn) + (tmpn < 10 ? 4 : 3);
	if (!(str = malloc(sizeof(char) * len)))
		return (NULL);
	str[0] = 'e';
	str[1] = (tens < 0) ? '-' : '+';
	str[--len] = '\0';
	(tmpn < 10) && (str[2] = '0');
	(tmpn == 0) && (str[3] = '0');
	while (len-- && tmpn)
	{
		str[len] = (tmpn % 10) + 48;
		tmpn = tmpn / 10;
	}
	return (str);
}

static int	display_e(t_tab *tab, int tens, char *res, char prefix)
{
	int		len;
	char	*nbr;

	tens = (tens < 1) ? (tens) : (tens - 1);
	if (!(nbr = generate_suffix(tens)))
	{
		free(res);
		return (0);
	}
	len = ft_strlen(nbr);
	len += (prefix && tab->flag[3]) ? (ft_strlen(res) + 1) : (ft_strlen(res));
	(!tab->flag[0]) && (pre_padding(tab, len));
	ft_putstr(res);
	free(res);
	ft_putstr(nbr);
	free(nbr);
	tab->len += len;
	(tab->flag[0]) && (padding(tab, ' ', tab->width - len, 1));
	return (1);
}

static char	*do_e(t_tab *tab, long double e, int *rnd, char prefix)
{
	uintmax_t	i;
	uintmax_t	precision;
	char		*tmp;

	i = 0;
	precision = (tab->spec == 'g') ? (tab->prec - 1) : (tab->prec);
	while (i <= precision)
		e = (++i) ? (e *= 10) : (e *= 10);
	e += 0.5;
	(prefix && !tab->flag[3]) && i++;
	(tab->prec >= 1) && i++;
	if (!(tmp = (char *)ft_calloc(sizeof(char), (i + 1))))
		return (NULL);
	while (tab->prec && precision--)
	{
		tmp[--i] = (uintmax_t)e % 10 + 48;
		e /= 10;
	}
	(tab->prec >= 1) && (tmp[--i] = '.');
	if ((uintmax_t)e % 10 + 48 == '0')
		*rnd = (e /= 10) ? 1 : 1;
	tmp[--i] = (uintmax_t)e % 10 + 48;
	(prefix && !tab->flag[3]) && (tmp[0] = prefix);
	return (tmp);
}

static int	get_tens(long double *e)
{
	int	tens;

	tens = 0;
	if (*e < 1)
	{
		while (*e && *e < 1)
			*e *= tens-- ? 10 : 10;
		*e /= 10;
	}
	else
		while (*e > 1)
			*e /= tens++ ? 10 : 10;
	return (tens);
}

int			conv_e(t_tab *tab)
{
	long double	e;
	int			tens;
	int			rnd;
	char		prefix;
	char		*res;

	rnd = 0;
	e = (tab->spec == 'g') ? (tab->g) : ((long double)va_arg(tab->ap, double));
	prefix = get_sign(tab, (e < 0 ? 1 : 0));
	e = (e < 0) ? -e : e;
	(tab->prec == -1) && (tab->prec = 6);
	tens = get_tens(&e);
	(!(tab->spec == 'g') && tens >= 0) && (tens = (e != 0) ? (tens) : (0));
	res = do_e(tab, e, &rnd, prefix);
	tens += rnd;
	res = ((tab->spec == 'g') && tab->prec > 0 && !tab->flag[4]) ?
			(trim_zeros(res, ft_strlen(res))) : (res);
	(prefix && tab->flag[3]) && (write(1, &prefix, 1));
	if (!(display_e(tab, tens, res, prefix)))
		return (0);
	return (1);
}
