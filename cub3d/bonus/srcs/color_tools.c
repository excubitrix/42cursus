/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 08:48:31 by floogman          #+#    #+#             */
/*   Updated: 2020/10/25 14:39:09 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_rgb(int trgb, char c)
{
	if (c == 'r')
		return ((trgb & 0x00FF0000) >> 16);
	if (c == 'g')
		return ((trgb & 0x0000FF00) >> 8);
	if (c == 'b')
		return (trgb & 0x000000FF);
	return (0);
}

int		create_trgb(int t, int r, int g, int b)
{
	return ((t << 24) + (r << 16) + (g << 8) + b);
}

int		add_shadow(double shd, int clr)
{
	return ((unsigned int)create_trgb(0, get_rgb(clr, 'r')
		* shd, get_rgb(clr, 'g') * shd, get_rgb(clr, 'b') * shd));
}

int		change_opc(double opc, int clr, int current)
{
	double	new[3];
	double	diff[3];

	diff[0] = get_rgb(clr, 'r') - get_rgb(current, 'r');
	diff[1] = get_rgb(clr, 'g') - get_rgb(current, 'g');
	diff[2] = get_rgb(clr, 'b') - get_rgb(current, 'b');
	new[0] = get_rgb(current, 'r') + (diff[0] * opc);
	new[1] = get_rgb(current, 'g') + (diff[1] * opc);
	new[2] = get_rgb(current, 'b') + (diff[2] * opc);
	return (create_trgb(0, new[0], new[1], new[2]));
}
