/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 19:25:06 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:04:02 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		isinv(int x, t_vec size, t_inv inv)
{
	return ((x < size.z && inv.i) || (x >= size.z && x <= size.z * 2
		&& inv.ii) || (x > size.z * 2 && x < size.z * 3 && inv.iii)
		|| (x > size.z * 3 && x < size.x && inv.iv));
}

void	ft_get_size(t_data *s, t_vec *size, t_img *tex, double var)
{
	double	scaler;

	scaler = (double)(s->win.w / var) / tex->w;
	size->x = tex->w * scaler;
	size->y = tex->h * scaler;
	size->z = size->x / 4;
	tex->step.x = tex->w / size->x;
	tex->step.y = tex->h / size->y;
}

void	draw_hit(t_data *s, double opc, int clr)
{
	int		x;
	int		y;

	y = 0;
	while (y < s->win.h)
	{
		x = 0;
		while (x < s->win.w)
		{
			put_pixel(s, x, y, change_opc(opc, clr, get_pixel(s->img, x, y)));
			x++;
		}
		y++;
	}
}

void	draw_flash(t_data *s)
{
	static double	i;
	static int		j;

	if (j / 7 == 1 || j / 8 == 1 || j / 9 == 1)
	{
		if (j / 8 == 1)
			i = 0.6;
		else
			i = 0.35;
	}
	else
		i = 0.15;
	j = j / 9 == 1 ? 0 : j;
	draw_hit(s, i, create_trgb(0, 255, 0, 0));
	j++;
}
