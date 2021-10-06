/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:40:53 by floogman          #+#    #+#             */
/*   Updated: 2020/05/02 14:42:06 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	get_sign(t_tab *tab, int is_neg)
{
	if (is_neg)
		return ('-');
	else if (tab->flag[1] == '+')
		return ('+');
	else if (tab->flag[2] == ' ')
		return (' ');
	return ('\0');
}

int		get_len(uintmax_t nbr)
{
	int len;

	len = 1;
	while ((nbr /= 10) > 0)
		len++;
	return (len);
}

char	*trim_zeros(char *tmp, int len)
{
	while (tmp[--len] == '0')
		tmp[len] = '\0';
	(tmp[len] == '.') && (tmp[len] = '\0');
	return (tmp);
}
