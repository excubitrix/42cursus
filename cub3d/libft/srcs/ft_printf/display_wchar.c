/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_wchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 10:00:13 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:55:29 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	wide_2(wint_t c)
{
	unsigned char	output[2];

	output[0] = (c >> 6) + 192;
	output[1] = ((c & 63) + 128);
	write(1, output, 2);
}

static void	wide_3(wint_t c)
{
	unsigned char	output[3];

	output[0] = (c >> 12) + 224;
	output[1] = ((c >> 6) & 63) + 128;
	output[2] = ((c & 63) + 128);
	write(1, output, 3);
}

static void	wide_4(wint_t c)
{
	unsigned char	output[4];

	output[0] = (c >> 18) + 240;
	output[1] = ((c >> 12) & 63) + 128;
	output[2] = ((c >> 6) & 63) + 128;
	output[3] = ((c & 63) + 128);
	write(1, output, 4);
}

void	display_wchar(t_tab *tab, wint_t c)
{
	if (c <= 127)
	{
		write(1, &c, 1);
		tab->len += 1;
	}
	else if (c >= 128 && c <= 2047)
	{
		wide_2(c);
		tab->len += 2;
	}
	else if (c >= 2048 && c <= 65535)
	{
		wide_3(c);
		tab->len += 3;
	}
	else
	{
		wide_4(c);
		tab->len += 4;
	}
}
