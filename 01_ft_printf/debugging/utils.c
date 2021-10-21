/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:40:53 by floogman          #+#    #+#             */
/*   Updated: 2021/10/04 10:48:37 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	trim_zeros(t_tab *tab, char *tmp, uintmax_t *i)
{
	if (tmp[*i] == '0' && !tmp[*i + 1] && tab->spec == 'g'
		&& tab->prec > 0 && !tab->flag[4])
		return (1);
	return (0);
}

char	*get_sign(t_tab *tab, int is_neg)
{
	if (is_neg)
		return ("-");
	if (tab->flag[1])
		return ("+");
	if (tab->flag[2])
		return (" ");
	return (NULL);
}

int	get_len(t_tab *tab, int len, char *prefix)
{
	if (len <= tab->prec && tab->prec >= 0)
		len = tab->prec;
	if (prefix)
		len += ft_strlen(prefix);
	if (len <= tab->width)
		tab->len += tab->width;
	else
		tab->len += len;
	return (len);
}

void	display_nbr(t_tab *tab, char *nbr, char *prefix, int len)
{
	int		p_len;
	int		n_len;

	if (prefix)
		p_len = ft_strlen(prefix);
	n_len = ft_strlen(nbr);
	if (!tab->flag[0])
		padding(tab, ' ', tab->width - len, 0);
	if (prefix)
		write(1, prefix, p_len);
	if (prefix && !tab->flag[0] && (tab->spec == 'x' || tab->spec == 'X'))
		padding(tab, '0', tab->prec - n_len - 2, 0);
	else
		padding(tab, '0', tab->prec - n_len, 0);
	write(1, nbr, n_len);
	if (tab->flag[0])
		padding(tab, ' ', tab->width - len, 0);
	free(nbr);
}
