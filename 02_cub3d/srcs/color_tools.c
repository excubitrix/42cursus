/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 08:48:31 by floogman          #+#    #+#             */
/*   Updated: 2020/12/25 14:40:16 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_r(int trgb)
{
	return ((trgb & 0x00FF0000) >> 16);
}

int		get_g(int trgb)
{
	return ((trgb & 0x0000FF00) >> 8);
}

int		get_b(int trgb)
{
	return (trgb & 0x000000FF);
}

int		create_trgb(int t, int r, int g, int b)
{
	return ((t << 24) + (r << 16) + (g << 8) + b);
}

int		add_shadow(double shd, int clr)
{
	return ((unsigned int)create_trgb(0, get_r(clr) * shd, get_g(clr) * shd,
		get_b(clr) * shd));
}
