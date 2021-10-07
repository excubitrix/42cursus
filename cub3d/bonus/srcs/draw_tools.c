/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 08:38:40 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:03:14 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_pixel(t_img img, int x, int y)
{
	char	*dst;
	int		clr;

	dst = img.addr + (y * img.ll + x * (img.bpp / 8));
	clr = *(unsigned int*)dst;
	return (clr);
}

int		get_pixel_img(t_data *s, int x, int y)
{
	t_img	tex;

	if (!s->plr.energy)
		tex = s->tex[ZERO];
	else if (s->plr.energy == 1)
		tex = s->tex[ONE];
	else if (s->plr.energy == 2)
		tex = s->tex[TWO];
	else
		tex = s->tex[THREE];
	return (get_pixel(tex, x, y));
}

void	put_pixel(t_data *s, int x, int y, int clr)
{
	char	*dst;

	dst = s->img.addr + (y * s->img.ll + x * (s->img.bpp / 8));
	*(unsigned int*)dst = clr;
}
