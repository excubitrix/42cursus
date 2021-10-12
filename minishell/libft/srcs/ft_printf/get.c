/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:35:46 by floogman          #+#    #+#             */
/*   Updated: 2020/03/21 17:12:07 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_flags(t_tab *tab)
{
	size_t	i;

	i = 0;
	tab->i++;
	while (tab->flags[i] != '\0')
	{
		while (tab->f[tab->i] == '-' && tab->f[tab->i + 1])
			(tab->i++ > 0) && (tab->flag[0] = '-');
		while (tab->f[tab->i] == '+' && tab->f[tab->i + 1])
			(tab->i++ > 0) && (tab->flag[1] = '+');
		while (tab->f[tab->i] == ' ' && tab->f[tab->i + 1])
			(tab->i++ > 0) && (tab->flag[2] = ' ');
		while (tab->f[tab->i] == '0' && tab->f[tab->i + 1])
			(tab->i++ > 0) && (tab->flag[3] = '0');
		while (tab->f[tab->i] == '#' && tab->f[tab->i + 1])
			(tab->i++ > 0) && (tab->flag[4] = '#');
		i++;
	}
}

void	get_width(t_tab *tab)
{
	if (tab->f[tab->i] == '*' && tab->f[tab->i + 1])
	{
		tab->width = (long)va_arg(tab->ap, int);
		if (tab->width < 0)
		{
			tab->flag[0] = '-';
			tab->width = -tab->width;
		}
		tab->i++;
	}
	while (ft_isdigit(tab->f[tab->i]) &&
		tab->f[tab->i + 1])
	{
		tab->width *= 10;
		tab->width += (tab->f[tab->i] - 48);
		tab->i++;
	}
}

void	get_precision(t_tab *tab)
{
	if (tab->f[tab->i] == '.' && tab->f[tab->i + 1])
	{
		tab->prec = 0;
		tab->i++;
	}
	if (tab->f[tab->i] == '*' && tab->f[tab->i + 1])
	{
		tab->prec = (long)va_arg(tab->ap, int);
		(tab->prec < 0) && (tab->prec = -1);
		tab->i++;
	}
	while (ft_isdigit(tab->f[tab->i]) &&
		tab->f[tab->i + 1])
	{
		tab->prec *= 10;
		tab->prec += (tab->f[tab->i] - 48);
		tab->i++;
	}
}

void	get_modifiers(t_tab *tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab->modis[i])
	{
		while ((tab->modis[i] == tab->f[tab->i]) && (tab->f[tab->i + 1]))
		{
			tab->modi[j] = tab->f[tab->i];
			tab->i++;
			j++;
		}
		i++;
	}
}
