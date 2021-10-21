/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:42:19 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:56:31 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	padding(t_tab *tab, char c, int len, int update)
{
	int	i;

	i = 0;
	if (len > 0)
	{
		while (i++ < len)
			write(1, &c, 1);
		if (update)
			tab->len += len;
	}
	return (SUCCESS);
}

int	pre_padding(t_tab *tab, int len)
{
	if (tab->flag[3])
		padding(tab, '0', tab->width - len, 1);
	else
		padding(tab, ' ', tab->width - len, 1);
	return (SUCCESS);
}
