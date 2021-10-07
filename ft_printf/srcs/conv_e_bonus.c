/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_e_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:20:44 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 10:45:37 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static char	*add_suffix(char *nbr, int len, int tens)
{
	char	*new;

	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
	{
		free(nbr);
		return (NULL);
	}
	ft_memcpy(new, nbr, ft_strlen(nbr));
	if (tens < 0)
		ft_memcpy(new + ft_strlen(new), "e-00", 4);
	else
		ft_memcpy(new + ft_strlen(new), "e+00", 4);
	if (tens < 0)
		tens = -tens;
	while (len-- && tens)
	{
		new[len] = (tens % 10) + 48;
		tens /= 10;
	}
	free(nbr);
	return (new);
}

static int	display_e(t_tab *tab, int tens, char *nbr, char *prefix)
{
	int		len;
	int		tmp;

	tmp = tens;
	if (tens < 0)
		tmp = -tens;
	len = ft_strlen(nbr) + 3 + (tmp < 10);
	tmp /= 10;
	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	nbr = add_suffix(nbr, len, tens);
	if (!nbr)
		return (FAILURE);
	display_f(tab, nbr, prefix);
	return (SUCCESS);
}

static int	do_e(t_tab *tab, long double e, int tens, char *prefix)
{
	uintmax_t	i;
	int			k;
	uintmax_t	prec;
	char		*tmp;

	i = 0;
	prec = (uintmax_t)tab->prec;
	while (i++ < (uintmax_t)tab->prec && (e - (long)e) > 0)
		e *= 10;
	k = i;
	e += 0.5;
	if ((long)e % 2 && e <= (double)((long)e))
		e -= 0.5;
	i = prec + 1 + (tab->prec > 0 || tab->flag[4]);
	tmp = get_double(tab, &e, &i, k);
	if (!tmp)
		return (FAILURE);
	tmp[--i] = ((uintmax_t)e % 10) + 48;
	if (display_e(tab, tens, tmp, prefix) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

static int	get_tens_e(long double *e)
{
	long double	rnd;
	int			tens;

	tens = 0;
	if (*e < 1)
	{
		while (*e && *e < 1)
			if (--tens)
				*e *= 10;
	}
	else
	{
		rnd = 0.5;
		while (*e + rnd >= 10)
		{
			if (++tens)
				*e /= 10;
			rnd /= 10;
		}
	}
	return (tens);
}

int	conv_e(t_tab *tab)
{
	long double	e;
	int			tens;
	char		*prefix;

	e = tab->g;
	if (tab->spec != 'g')
		e = (long double)va_arg(tab->ap, double);
	if (isinf(e) || isnan(e))
		return (display_exp(tab, e));
	prefix = get_sign(tab, signbit(e));
	if (signbit(e))
		e = -e;
	if (tab->prec < 0)
		tab->prec = 6;
	tens = get_tens_e(&e);
	if (do_e(tab, e, tens, prefix) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
