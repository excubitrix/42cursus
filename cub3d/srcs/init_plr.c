/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_plr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 11:06:04 by floogman          #+#    #+#             */
/*   Updated: 2021/01/23 17:49:43 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_pos(t_data *s, char dir, double x, double y)
{
	t_vec	pos;
	t_vec	ray;
	t_vec	dlt;

	pos.x = x;
	pos.y = y;
	s->pos = pos;
	ray.x = 0;
	ray.y = 0;
	s->ray = ray;
	dlt.x = 0;
	dlt.y = 0;
	s->dlt = dlt;
	return (set_dir(s, dir));
}

int		set_dir(t_data *s, char c)
{
	t_vec	dir;
	t_vec	step;

	if (c == 'N')
		dir.y = -1;
	if (c == 'S')
		dir.y = 1;
	if (c == 'W')
		dir.x = -1;
	if (c == 'E')
		dir.x = 1;
	s->dir = dir;
	step.x = 0;
	step.y = 0;
	s->step = step;
	return (set_pln(s, c));
}

int		set_pln(t_data *s, char c)
{
	t_vec	pln;
	t_vec	side;
	double	scaler;

	side.x = 0;
	side.y = 0;
	scaler = (double)s->win.h / (double)s->win.w;
	if (c == 'N')
		pln.x = (0.66 / scaler);
	if (c == 'S')
		pln.x = -(0.66 / scaler);
	if (c == 'W')
		pln.y = -(0.66 / scaler);
	if (c == 'E')
		pln.y = (0.66 / scaler);
	s->pln = pln;
	s->side = side;
	return (0);
}
