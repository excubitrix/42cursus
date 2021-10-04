/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:05:40 by floogman          #+#    #+#             */
/*   Updated: 2021/10/04 18:10:30 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	reinit_tab(t_tab *tab)
{
	char	*ptr;

	tab->spec = '\0';
	tab->g = -1.0;
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
		ptr = ft_strchr(tab->conv_mask, tab->f[tab->i]);
		if (ptr)
			tab->spec = *ptr;
	}
}

void	init_tab(t_tab *tab, const char *format)
{
	tab->f = format;
	tab->len = 0;
	tab->i = 0;
	tab->conv_mask = "cspdiuxX%nfge";
	tab->conv_ptr[0] = &conv_c;
	tab->conv_ptr[1] = &conv_s;
	tab->conv_ptr[2] = &conv_p;
	tab->conv_ptr[3] = &conv_d;
	tab->conv_ptr[4] = &conv_d;
	tab->conv_ptr[5] = &conv_u;
	tab->conv_ptr[6] = &conv_x;
	tab->conv_ptr[7] = &conv_x;
	tab->conv_ptr[8] = &display_mod;
	tab->conv_ptr[9] = &conv_n;
	tab->conv_ptr[10] = &conv_f;
	tab->conv_ptr[11] = &conv_g;
	tab->conv_ptr[12] = &conv_e;
	tab->modis = "lh";
}
