/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:03:05 by floogman          #+#    #+#             */
/*   Updated: 2021/10/04 18:09:51 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	display_mod(t_tab *tab)
{
	if (!tab->flag[0])
		pre_padding(tab, 1);
	write(1, "%", 1);
	tab->len++;
	if (tab->flag[0])
		padding(tab, ' ', tab->width - 1, 1);
	return (SUCCESS);
}

static int	parser(t_tab *tab, int counter)
{
	int		i;

	while (tab->f[tab->i])
	{
		if (tab->f[tab->i] == '%')
		{
			write(1, &tab->f[tab->i - counter], counter);
			tab->len += counter;
			reinit_tab(tab);
			i = -1;
				// if (!ft_strncmp(&tab->spec, tab->conv_str[i], 1))
			while (++i < 13)
				if (!ft_strncmp(&tab->spec, &tab->conv_mask[i], 1))
					if (tab->conv_ptr[i](tab) != SUCCESS)
						return (FAILURE);
			counter = 0;
		}
		else
			counter++;
		tab->i++;
	}
	write(1, &tab->f[tab->i - counter], counter);
	tab->len += counter;
	return (SUCCESS);
}

int	ft_printf(const char *format, ...)
{
	t_tab	tab;

	init_tab(&tab, format);
	if (format)
	{
		va_start(tab.ap, format);
		if (ft_strncmp(format, "%", 2) && parser(&tab, 0) != SUCCESS)
		{
			va_end(tab.ap);
			return (-1);
		}
		va_end(tab.ap);
	}
	return (tab.len);
}
