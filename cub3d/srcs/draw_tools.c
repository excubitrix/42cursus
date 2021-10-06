/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 08:38:40 by floogman          #+#    #+#             */
/*   Updated: 2021/01/07 12:07:46 by floogman         ###   ########.fr       */
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

void	put_pixel(t_data *s, int x, int y, int clr)
{
	char	*dst;

	dst = s->img.addr + (y * s->img.ll + x * (s->img.bpp / 8));
	*(unsigned int*)dst = clr;
}

void	draw_ver_line(t_data *s, t_xy xy, int end, int clr)
{
	int		start;

	start = xy.y;
	while (start <= end)
	{
		put_pixel(s, xy.x, start, clr);
		start++;
	}
}

void	draw_bg(t_data *s, int x)
{
	t_xy	xy;

	xy.x = x;
	xy.y = 0;
	draw_ver_line(s, xy, s->win.h / 2, s->ceiling);
	xy.y = s->win.h / 2;
	draw_ver_line(s, xy, s->win.h - 1, s->floor);
}
