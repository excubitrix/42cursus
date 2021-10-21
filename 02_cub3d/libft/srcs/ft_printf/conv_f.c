/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:42:39 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 10:24:38 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	display_f(t_tab *tab, char *nbr, char *prefix)
{
	int		len;

	len = ft_strlen(nbr) + (prefix != NULL);
	if (prefix && tab->flag[3])
		write(1, prefix, 1);
	if (!tab->flag[0])
		pre_padding(tab, len);
	if (prefix && !tab->flag[3])
		write(1, prefix, 1);
	write(1, nbr, len - (prefix != NULL));
	tab->len += len;
	if (tab->flag[0])
		padding(tab, ' ', tab->width - len, 1);
	free(nbr);
}

char	*get_double(t_tab *tab, long double *d, uintmax_t *i, int k)
{
	uintmax_t	prec;
	char		*tmp;

	tmp = ft_calloc((*i + 1), sizeof(char));
	if (!tmp)
		return (NULL);
	prec = (uintmax_t)tab->prec;
	while (tab->prec && k <= tab->prec && prec-- && (k++ || !k))
	{
		tmp[--(*i)] = '0';
		if (trim_zeros(tab, tmp, i))
			tmp[*i] = '\0';
	}
	while (tab->prec && prec--)
	{
		tmp[--(*i)] = ((uintmax_t)(*d) % 10) + 48;
		if (trim_zeros(tab, tmp, i))
			tmp[*i] = '\0';
		*d /= 10;
	}
	if ((tmp[*i] && tab->prec > 0) || tab->flag[4])
		tmp[--(*i)] = '.';
	else if (tab->prec > 0)
		tmp[--(*i)] = '\0';
	return (tmp);
}

static int	do_f(t_tab *tab, long double f, int tens, char *prefix)
{
	uintmax_t	i;
	uintmax_t	prec;
	char		*tmp;
	int			k;

	i = 0;
	while (i++ < (uintmax_t)tab->prec && (f - (long)f) > 0)
		f *= 10;
	f += 0.5;
	if (tens == 1 && (long)f % 2 && f <= (double)((long)f))
		f -= 0.5;
	k = i;
	prec = tab->prec;
	i = prec + tens + (tab->prec > 0 || tab->flag[4]);
	tmp = get_double(tab, &f, &i, k);
	if (!tmp)
		return (FAILURE);
	while (tens--)
	{
		tmp[--i] = ((uintmax_t)f % 10) + 48;
		f /= 10;
	}
	display_f(tab, tmp, prefix);
	return (SUCCESS);
}

static int	get_tens_f(t_tab *tab, long double f)
{
	int		tens;
	long	tmp;

	tens = 1;
	tmp = (long)(f + 0.5);
	if (tmp == LONG_MIN)
		tmp = LONG_MAX;
	if (tmp >= 1)
	{
		tmp /= 10;
		while (tmp)
		{
			tmp /= 10;
			tens++;
		}
	}
	if (tab->spec == 'g' && f >= 1)
		tab->prec -= tens;
	return (tens);
}

int	conv_f(t_tab *tab)
{
	long double	f;
	char		*prefix;

	f = tab->g;
	if (tab->spec != 'g')
		f = (long double)va_arg(tab->ap, double);
	prefix = get_sign(tab, f < 0);
	if (f < 0)
		f = -f;
	if (tab->prec < 0)
		tab->prec = 6;
	if (do_f(tab, f, get_tens_f(tab, f), prefix) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
