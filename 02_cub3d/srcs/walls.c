/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 14:46:03 by floogman          #+#    #+#             */
/*   Updated: 2021/01/19 14:38:27 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_step(t_data *s)
{
	if (s->ray.x < 0)
	{
		s->step.x = -1;
		s->side.x = (s->pos.x - s->map.x) * s->dlt.x;
	}
	else
	{
		s->step.x = 1;
		s->side.x = (s->map.x + 1.0 - s->pos.x) * s->dlt.x;
	}
	if (s->ray.y < 0)
	{
		s->step.y = -1;
		s->side.y = (s->pos.y - s->map.y) * s->dlt.y;
	}
	else
	{
		s->step.y = 1;
		s->side.y = (s->map.y + 1.0 - s->pos.y) * s->dlt.y;
	}
}

int		find_wall(t_data *s, int *side, int *face)
{
	while (1)
	{
		if (s->side.x < s->side.y)
		{
			s->side.x += s->dlt.x;
			s->map.x += s->step.x;
			*face = s->ray.x < 0 ? 'W' : 'E';
			*side = 0;
		}
		else
		{
			s->side.y += s->dlt.y;
			s->map.y += s->step.y;
			*face = s->ray.y > 0 ? 'S' : 'N';
			*side = 1;
		}
		if (s->map.x < 0 || s->map.x > s->map.w - 1
			|| s->map.y < 0 || s->map.y > s->map.h - 1)
			return (0);
		if (s->map.ptr[s->map.y * s->map.w + s->map.x] == '1')
			return (1);
	}
}

void	calc_height(t_data *s, int side, int *y, int nbr)
{
	if (side == 0)
		s->v.pwd = (s->map.x - s->pos.x + (1 - s->step.x) / 2) / s->ray.x;
	else
		s->v.pwd = (s->map.y - s->pos.y + (1 - s->step.y) / 2) / s->ray.y;
	s->v.h = s->win.h / s->v.pwd;
	s->v.start.y = (int)(-s->v.h / 2 + s->win.h / 2);
	if (s->v.start.y < 0)
		s->v.start.y = 0;
	s->v.end.y = (int)(s->v.h / 2 + s->win.h / 2);
	if (s->v.end.y >= s->win.h)
		s->v.end.y = s->win.h - 1;
	if (side == 0)
		s->v.wallx = s->pos.y + s->v.pwd * s->ray.y;
	else
		s->v.wallx = s->pos.x + s->v.pwd * s->ray.x;
	s->v.wallx -= floor(s->v.wallx);
	s->tex[(nbr)].x = (s->tex[(nbr)].h - 1) - (int)(s->v.wallx
		* (double)(s->tex[(nbr)].h));
	if ((side == 0 && s->ray.x > 0) || (side == 1 && s->ray.y < 0))
		s->tex[(nbr)].x = s->tex[(nbr)].w - s->tex[(nbr)].x - 1;
	*y = s->v.start.y;
}

void	draw_wall(t_data *s, int x, int side, int face)
{
	int		y;
	int		nbr;
	int		clr;

	nbr = gnl_strchr("NSWE", (char)face);
	calc_height(s, side, &y, nbr);
	s->tex[nbr].step = (double)s->tex[nbr].h / s->v.h;
	s->tex[nbr].pos = (y - s->win.h / 2 + s->v.h / 2) * s->tex[nbr].step;
	while (y <= s->v.end.y)
	{
		s->tex[nbr].y = (int)s->tex[nbr].pos & (s->tex[nbr].h - 1);
		s->tex[nbr].pos += s->tex[nbr].step;
		clr = get_pixel(s->tex[nbr], s->tex[nbr].x, s->tex[nbr].y);
		if (!side)
			clr = add_shadow(0.5, clr);
		put_pixel(s, x, y, clr);
		y++;
	}
}

void	cast_walls(t_data *s)
{
	double	cam;
	int		side;
	int		face;
	int		x;

	x = 0;
	while (x < s->win.w)
	{
		cam = 2 * x / (double)s->win.w - 1;
		s->ray.x = s->dir.x + s->pln.x * cam;
		s->ray.y = s->dir.y + s->pln.y * cam;
		s->dlt.x = fabs(1 / s->ray.x);
		s->dlt.y = fabs(1 / s->ray.y);
		s->map.x = s->pos.x;
		s->map.y = s->pos.y;
		calc_step(s);
		draw_bg(s, x);
		if (find_wall(s, &side, &face))
			draw_wall(s, x, side, face);
		s->zbuffer[x] = s->v.pwd;
		x++;
	}
}
