/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceil_sky.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:27:06 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:02:46 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_sky(t_data *s, double *angle, int x)
{
	s->v.screenx = 2 * x / (double)s->win.w - 1;
	s->ray.dir.x = s->plr.dir.x + s->pln.x * s->v.screenx;
	s->ray.dir.y = s->plr.dir.y + s->pln.y * s->v.screenx;
	*angle = atan(s->ray.dir.y / s->ray.dir.x) * s->tex[SKY].w / M_PI;
}

int		draw_sky(t_data *s, int y, int x)
{
	double	angle;
	t_vec	step;
	t_vec	tex;

	step.x = (s->tex[SKY].w / (s->win.h * 0.01)) / (360.0 / s->scaler);
	step.y = s->tex[SKY].h / ((s->win.h / 2) + (s->win.h * 0.33 / s->scaler));
	while (x < s->win.w)
	{
		calc_sky(s, &angle, x);
		tex.x = x * step.x + angle;
		tex.y = (y + (s->win.h * 0.33 / s->scaler) - s->ray.pitch) * step.y;
		if (tex.x > s->tex[SKY].w)
			tex.x = fmod(tex.x, s->tex[SKY].w);
		put_pixel(s, x, y, get_pixel(s->tex[SKY], tex.x, tex.y));
		x++;
	}
	return (0);
}

int		draw_floor(t_data *s, t_vars v, int y, int nbr)
{
	t_vec	cell;
	t_xy	tex;
	int		x;

	x = 0;
	cell.x = s->plr.pos.x + v.rowdst * v.rayo.x;
	cell.y = s->plr.pos.y + v.rowdst * v.rayo.y;
	while (x < s->win.w)
	{
		tex.x = (int)(s->tex[nbr].w * (cell.x - (int)cell.x))
			& (s->tex[nbr].w - 1);
		tex.y = (int)(s->tex[nbr].h * (cell.y - (int)cell.y))
			& (s->tex[nbr].h - 1);
		cell.x += v.step.x;
		cell.y += v.step.y;
		put_pixel(s, x, y, add_shadow((10 - v.rowdst) / 10 < 0 ? 0.01
			: (10 - v.rowdst) / 10, get_pixel(s->tex[nbr], tex.x, tex.y)));
		x++;
	}
	return (0);
}

/*
**	To render a ceiling instead of the sky, replace line 94 with the following:
**	is_floor ? draw_floor(s, s->v, y, FLOOR) :
**		draw_floor(s, s->v, y, CEILING);
*/

void	cast_floor(t_data *s, int y)
{
	double	cam_z;
	int		is_floor;

	cam_z = 0;
	while (y < s->win.h)
	{
		is_floor = y > s->win.h / 2 + s->ray.pitch - 1;
		s->v.rayo.x = s->plr.dir.x - s->pln.x;
		s->v.rayo.y = s->plr.dir.y - s->pln.y;
		s->v.rayi.x = s->plr.dir.x + s->pln.x;
		s->v.rayi.y = s->plr.dir.y + s->pln.y;
		s->v.p = is_floor ? (y - s->win.h / 2 - s->ray.pitch)
			: (s->win.h / 2 - y + s->ray.pitch);
		cam_z = is_floor ? (0.5 * s->win.h + s->plr.pos.z)
			: (0.5 * s->win.h - s->plr.pos.z);
		s->v.rowdst = cam_z / s->v.p;
		s->v.step.x = s->v.rowdst * (s->v.rayi.x - s->v.rayo.x) / s->win.w;
		s->v.step.y = s->v.rowdst * (s->v.rayi.y - s->v.rayo.y) / s->win.w;
		is_floor ? draw_floor(s, s->v, y, FLOOR) : draw_sky(s, y, 0);
		y++;
	}
}
