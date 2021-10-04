/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:35:46 by floogman          #+#    #+#             */
/*   Updated: 2021/04/28 14:01:39 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_flags(t_tab *tab)
{
	int		i;

	tab->i++;
	i = -1;
	while (++i < 5)
	{
		while (tab->f[tab->i] == '-' && tab->f[++tab->i])
			tab->flag[0] = '-';
		while (tab->f[tab->i] == '+' && tab->f[++tab->i])
			tab->flag[1] = '+';
		while (tab->f[tab->i] == ' ' && tab->f[++tab->i])
			tab->flag[2] = ' ';
		while (tab->f[tab->i] == '0' && tab->f[++tab->i])
			tab->flag[3] = '0';
		while (tab->f[tab->i] == '#' && tab->f[++tab->i])
			tab->flag[4] = '#';
	}
}

void	get_width(t_tab *tab)
{
	if (tab->f[tab->i] == '*' && tab->f[++tab->i])
	{
		tab->width = (long)va_arg(tab->ap, int);
		if (tab->width < 0)
		{
			tab->flag[0] = '-';
			tab->width = -tab->width;
		}
	}
	while (ft_isdigit(tab->f[tab->i]) && tab->f[tab->i + 1])
		tab->width = (tab->width * 10) + (tab->f[tab->i++] - 48);
}

void	get_precision(t_tab *tab)
{
	if (tab->f[tab->i] == '.' && tab->f[++tab->i])
	{
		tab->prec = 0;
		if (tab->f[tab->i] == '*' && tab->f[++tab->i])
		{
			tab->prec = (long)va_arg(tab->ap, int);
			if (tab->prec < 0)
				tab->prec = -1;
		}
		else
			while (ft_isdigit(tab->f[tab->i]) && tab->f[tab->i + 1])
				tab->prec = (tab->prec * 10) + (tab->f[tab->i++] - 48);
	}
}

void	get_modifiers(t_tab *tab)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (tab->modis[++i])
		while ((tab->modis[i] == tab->f[tab->i]) && (tab->f[tab->i + 1]))
			tab->modi[j++] = tab->f[tab->i++];
}
