/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:05:40 by floogman          #+#    #+#             */
/*   Updated: 2020/03/21 17:12:11 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_tab	*init_tab(t_tab *tab)
{
	tab->len = 0;
	tab->i = 0;
	tab->convs = "cspdiuxX%nfge";
	tab->flags = "-0.*+ #";
	tab->modis = "lh";
	return (tab);
}

void	reinit_tab(t_tab *tab)
{
	tab->spec = '\0';
	tab->g = (double)-1;
	ft_bzero(tab->flag, 6);
	ft_bzero(tab->modi, 4);
	tab->prec = -1;
	tab->width = 0;
	if (tab->f[tab->i + 1])
	{
		get_flags(tab);
		get_width(tab);
		get_precision(tab);
		get_modifiers(tab);
		if (ft_strchr(tab->convs, tab->f[tab->i]))
			(tab->spec = *ft_strchr(tab->convs, tab->f[tab->i]));
	}
}
