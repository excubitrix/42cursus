/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:05:40 by floogman          #+#    #+#             */
/*   Updated: 2021/10/04 13:00:19 by floogman         ###   ########.fr       */
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
		if (tab->spec == 'i')
			tab->spec = 'd';
	}
}

void	init_conv_ptrs(t_tab *tab)
{
	// tab->conv_str[0] = "c";
	// tab->conv_str[1] = "s";
	// tab->conv_str[2] = "p";
	// tab->conv_str[3] = "d";
	// tab->conv_str[4] = "u";
	// tab->conv_str[5] = "x";
	// tab->conv_str[6] = "X";
	// tab->conv_str[7] = "%";
	// tab->conv_str[8] = "n";
	// tab->conv_str[9] = "f";
	// tab->conv_str[10] = "g";
	// tab->conv_str[11] = "e";
	tab->conv_ptr[0] = &conv_c;
	tab->conv_ptr[1] = &conv_s;
	tab->conv_ptr[2] = &conv_p;
	tab->conv_ptr[3] = &conv_d;
	tab->conv_ptr[4] = &conv_u;
	tab->conv_ptr[5] = &conv_x;
	tab->conv_ptr[6] = &conv_x;
	tab->conv_ptr[7] = &display_mod;
	tab->conv_ptr[8] = &conv_n;
	tab->conv_ptr[9] = &conv_f;
	tab->conv_ptr[10] = &conv_g;
	tab->conv_ptr[11] = &conv_e;
}

void	init_tab(t_tab *tab, const char *format)
{
	tab->f = format;
	tab->len = 0;
	tab->i = 0;
	tab->conv_mask = "cspdiuxX%nfge";
	init_conv_ptrs(tab);
	tab->modis = "lh";
}
