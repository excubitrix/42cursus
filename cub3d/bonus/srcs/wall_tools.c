/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 09:20:15 by floogman          #+#    #+#             */
/*   Updated: 2021/01/22 09:54:38 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_grid_lines(t_data *s, t_vec *ctr, int *side, int *face)
{
	if (s->dst.x < s->dst.y)
	{
		s->dst.x += s->ray.dlt.x;
		s->map.x += s->ray.step.x;
		*face = s->ray.dir.x < 0 ? 'W' : 'E';
		*side = 0;
	}
	else
	{
		s->dst.y += s->ray.dlt.y;
		s->map.y += s->ray.step.y;
		*face = s->ray.dir.y > 0 ? 'S' : 'N';
		*side = 1;
	}
	ctr->x = s->map.x + (s->ray.step.x / 2);
	ctr->y = s->map.y + (s->ray.step.y / 2);
}

double	check_next(t_data *s, t_ray ray, t_vec pos, int side)
{
	int		x;
	int		y;

	x = s->map.x;
	y = s->map.y;
	while (1)
	{
		if (s->dst.x < s->dst.y)
		{
			x += ray.step.x;
			side = 0;
		}
		else
		{
			y += ray.step.y;
			side = 1;
		}
		if (get_tile(s, x, y) != '0')
		{
			if (!side)
				return ((x - pos.x + (1 - ray.step.x) / 2) / ray.dir.x);
			else
				return ((y - pos.y + (1 - ray.step.y) / 2) / ray.dir.y);
		}
	}
}

void	calc_pwd_wall(t_data *s, int side)
{
	if (!side)
		s->v.pwd = (s->map.x - s->plr.pos.x + (1 - s->ray.step.x) / 2)
		/ s->ray.dir.x;
	else
		s->v.pwd = (s->map.y - s->plr.pos.y + (1 - s->ray.step.y) / 2)
		/ s->ray.dir.y;
}

void	calc_pwd_door(t_data *s, t_vec ctr, int face)
{
	if (face == 'W' || face == 'E')
		s->v.pwd = (ctr.x - s->plr.pos.x + (1 - s->ray.step.x) / 2)
		/ s->ray.dir.x;
	if (face == 'N' || face == 'S')
		s->v.pwd = (ctr.y - s->plr.pos.y + (1 - s->ray.step.y) / 2)
		/ s->ray.dir.y;
}
