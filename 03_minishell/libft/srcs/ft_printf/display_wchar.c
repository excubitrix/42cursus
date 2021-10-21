/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_wchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 10:00:13 by floogman          #+#    #+#             */
/*   Updated: 2020/03/21 17:12:02 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		wide_4(wint_t c)
{
	unsigned char output[4];

	output[0] = (c >> 18) + 240;
	output[1] = ((c >> 12) & 63) + 128;
	output[2] = ((c >> 6) & 63) + 128;
	output[3] = ((c & 63) + 128);
	write(1, output, 4);
}

static void		wide_3(wint_t c)
{
	unsigned char output[3];

	output[0] = (c >> 12) + 224;
	output[1] = ((c >> 6) & 63) + 128;
	output[2] = ((c & 63) + 128);
	write(1, output, 3);
}

static void		wide_2(wint_t c)
{
	unsigned char output[2];

	output[0] = (c >> 6) + 192;
	output[1] = ((c & 63) + 128);
	write(1, output, 2);
}

void			display_wchar(t_tab *tab, wint_t c)
{
	if (c <= 127)
	{
		tab->len += 1;
		write(1, &c, 1);
	}
	if (c >= 128 && c <= 2047)
	{
		tab->len += 2;
		wide_2(c);
	}
	if (c >= 2048 && c <= 65535)
	{
		tab->len += 3;
		wide_3(c);
	}
	if (c >= 65536)
	{
		tab->len += 4;
		wide_4(c);
	}
}
