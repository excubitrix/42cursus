/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 14:44:43 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:05:30 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move(t_data *s, double varx, double vary, double movespeed)
{
	double	new;
	char	c;

	new = s->plr.pos.x + varx * movespeed;
	c = get_tile(s, (int)(new), (int)s->plr.pos.y);
	if (c == 'i' || c == 'h' || c == '0')
		s->plr.pos.x = new;
	new = s->plr.pos.y + vary * movespeed;
	c = get_tile(s, (int)s->plr.pos.x, (int)(new));
	if (c == 'i' || c == 'h' || c == '0')
		s->plr.pos.y = new;
}

void	ft_rotate(t_data *s, double var)
{
	double	olddirx;
	double	oldplnx;

	olddirx = s->plr.dir.x;
	s->plr.dir.x = s->plr.dir.x * cos(var) - s->plr.dir.y * sin(var);
	s->plr.dir.y = olddirx * sin(var) + s->plr.dir.y * cos(var);
	oldplnx = s->pln.x;
	s->pln.x = s->pln.x * cos(var) - s->pln.y * sin(var);
	s->pln.y = oldplnx * sin(var) + s->pln.y * cos(var);
}

void	change_pitch(t_data *s, int up, double movespeed)
{
	if (up)
	{
		s->ray.pitch += ((s->win.h * 0.5) / s->scaler) * movespeed;
		if (s->ray.pitch > ((s->win.h * 0.25) / s->scaler))
			s->ray.pitch = ((s->win.h * 0.25) / s->scaler);
	}
	else
	{
		s->ray.pitch -= ((s->win.h * 0.5) / s->scaler) * movespeed;
		if (s->ray.pitch < -((s->win.h * 0.25) / s->scaler))
			s->ray.pitch = -((s->win.h * 0.25) / s->scaler);
	}
}

void	jumping(t_data *s, int jump, double movespeed)
{
	double	z;

	if (jump)
	{
		s->key.space = 1;
		s->key.jump = 1;
		s->plr.pos.z = ((s->win.h * 0.2) / s->scaler);
	}
	else
	{
		if (s->key.jump)
			movespeed *= 2;
		if (s->plr.pos.z > 0)
		{
			z = s->plr.pos.z - ((s->win.h * 0.12) / s->scaler) * movespeed;
			s->plr.pos.z = 0 > z ? 0 : z;
		}
		if (s->plr.pos.z == 0)
			s->key.jump = 0;
	}
}

int		movement(t_data *s, double rotspeed, double movespeed)
{
	if (s->key.w)
		ft_move(s, s->plr.dir.x, s->plr.dir.y, movespeed);
	if (s->key.s)
		ft_move(s, -s->plr.dir.x, -s->plr.dir.y, movespeed);
	if (s->key.a)
		ft_move(s, -s->pln.x, -s->pln.y, movespeed);
	if (s->key.d)
		ft_move(s, s->pln.x, s->pln.y, movespeed);
	if (s->key.shift)
		s->plr.pos.z = -((s->win.h * 0.09) / s->scaler);
	if (s->key.right)
		ft_rotate(s, rotspeed);
	if (s->key.left)
		ft_rotate(s, -rotspeed);
	if (s->key.up)
		change_pitch(s, 1, movespeed);
	if (s->key.down)
		change_pitch(s, 0, movespeed);
	return (0);
}
