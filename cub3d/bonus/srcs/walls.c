/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 14:46:03 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:07:30 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_step(t_data *s)
{
	if (s->ray.dir.x < 0)
	{
		s->ray.step.x = -1;
		s->dst.x = (s->plr.pos.x - s->map.x) * s->ray.dlt.x;
	}
	else
	{
		s->ray.step.x = 1;
		s->dst.x = (s->map.x + 1.0 - s->plr.pos.x) * s->ray.dlt.x;
	}
	if (s->ray.dir.y < 0)
	{
		s->ray.step.y = -1;
		s->dst.y = (s->plr.pos.y - s->map.y) * s->ray.dlt.y;
	}
	else
	{
		s->ray.step.y = 1;
		s->dst.y = (s->map.y + 1.0 - s->plr.pos.y) * s->ray.dlt.y;
	}
}

void	calc_slice(t_data *s, int side, int *y, int nbr)
{
	s->v.h = s->win.h / s->v.pwd;
	s->v.start.y = (int)(-s->v.h / 2 + s->win.h / 2 + s->ray.pitch
		+ (s->plr.pos.z / s->v.pwd));
	if (s->v.start.y < 0)
		s->v.start.y = 0;
	s->v.end.y = (int)(s->v.h / 2 + s->win.h / 2 + s->ray.pitch
		+ (s->plr.pos.z / s->v.pwd));
	if (s->v.end.y >= s->win.h)
		s->v.end.y = s->win.h - 1;
	*y = s->v.start.y;
	s->v.wallx = !side ? s->plr.pos.y + s->v.pwd * s->ray.dir.y
		: s->plr.pos.x + s->v.pwd * s->ray.dir.x;
	s->v.wallx -= floor(s->v.wallx);
	s->tex[(nbr)].x = (s->tex[(nbr)].h - 1) - (int)(s->v.wallx
		* (double)(s->tex[(nbr)].h));
	if ((!side && s->ray.dir.x > 0) || (side && s->ray.dir.y < 0))
		s->tex[(nbr)].x = s->tex[(nbr)].w - s->tex[(nbr)].x - 1;
	s->tex[nbr].step.y = (double)s->tex[nbr].h / s->v.h;
	s->tex[nbr].pos.y = (double)(*y - s->ray.pitch - (s->plr.pos.z / s->v.pwd)
		- s->win.h / 2 + s->v.h / 2) * s->tex[nbr].step.y;
}

int		draw_wall(t_data *s, int x, int side, int nbr)
{
	int		clr;
	int		y;

	calc_slice(s, side, &y, nbr);
	while (y <= s->v.end.y)
	{
		s->tex[nbr].y = (int)s->tex[nbr].pos.y & (s->tex[nbr].h - 1);
		s->tex[nbr].pos.y += s->tex[nbr].step.y;
		clr = get_pixel(s->tex[nbr], s->tex[nbr].x, s->tex[nbr].y);
		clr = add_shadow((10 - s->v.pwd) / 10 < 0 ? 0.01 : (10 - s->v.pwd)
			/ 10, clr);
		if ((nbr >= s->door[0][0] && nbr <= s->door[1][4]) && !clr)
			return (0);
		else
			put_pixel(s, x, y, clr);
		y++;
	}
	return (1);
}

void	find_wall(t_data *s, t_vars *v, int snbr, int x)
{
	char	c;

	while (1)
	{
		check_grid_lines(s, &s->map.ctr, &v->side, &v->face);
		c = get_tile(s, s->map.x, s->map.y);
		if (c == '1')
		{
			calc_pwd_wall(s, v->side);
			draw_wall(s, x, v->side, gnl_strchr("NSWE", (char)v->face));
			break ;
		}
		else if (c == 'I' || c == 'i' || c == 'H' || c == 'h')
		{
			snbr = get_snbr(s, s->map.x, s->map.y);
			if (((c == 'I' || c == 'i') && (v->face == 'W' || v->face == 'E'))
			|| ((c == 'H' || c == 'h') && (v->face == 'S' || v->face == 'N')))
			{
				calc_pwd_door(s, s->map.ctr, v->face);
				if (s->v.pwd < check_next(s, s->ray, s->plr.pos, 0))
					if (draw_wall(s, x, v->side, s->spr[snbr]->tex))
						break ;
			}
		}
	}
}

void	cast_walls(t_data *s, int x)
{
	double	cam;

	while (x < s->win.w)
	{
		cam = 2 * x / (double)s->win.w - 1;
		s->ray.dir.x = s->plr.dir.x + s->pln.x * cam;
		s->ray.dir.y = s->plr.dir.y + s->pln.y * cam;
		s->ray.dlt.x = fabs(1 / s->ray.dir.x);
		s->ray.dlt.y = fabs(1 / s->ray.dir.y);
		s->map.x = s->plr.pos.x;
		s->map.y = s->plr.pos.y;
		calc_step(s);
		find_wall(s, &s->v, 0, x);
		s->zbuffer[x] = s->v.pwd;
		x++;
	}
}
