/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:42:19 by floogman          #+#    #+#             */
/*   Updated: 2020/03/21 17:12:09 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		padding(t_tab *tab, char c, int len, int update)
{
	int	printed;

	printed = 0;
	if (len > 0)
	{
		while (printed++ < len)
			ft_putchar(c);
		(update) && (tab->len += len);
	}
	return (1);
}

int		pre_padding(t_tab *tab, int len)
{
	if (tab->flag[3])
		padding(tab, '0', tab->width - len, 1);
	else
		padding(tab, ' ', tab->width - len, 1);
	return (1);
}
