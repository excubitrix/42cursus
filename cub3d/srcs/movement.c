/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 14:44:43 by floogman          #+#    #+#             */
/*   Updated: 2021/01/19 08:52:55 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move(t_data *s, double varx, double vary)
{
	double	movespeed;
	double	new;

	movespeed = 5.0 / 60;
	new = s->pos.x + varx * movespeed;
	if (s->pos.y >= 0.5 && s->pos.y < s->map.h - 0.5
		&& new >= 0.5 && new < s->map.w - 0.5)
		s->pos.x = new;
	new = s->pos.y + vary * movespeed;
	if (s->pos.x >= 0.5 && s->pos.x < s->map.w - 0.5
		&& new >= 0.5 && new < s->map.h - 0.5)
		s->pos.y = new;
}

void	ft_rotate(t_data *s, double var)
{
	double	olddirx;
	double	oldplnx;

	olddirx = s->dir.x;
	s->dir.x = s->dir.x * cos(var) - s->dir.y * sin(var);
	s->dir.y = olddirx * sin(var) + s->dir.y * cos(var);
	oldplnx = s->pln.x;
	s->pln.x = s->pln.x * cos(var) - s->pln.y * sin(var);
	s->pln.y = oldplnx * sin(var) + s->pln.y * cos(var);
}

int		movement(t_data *s)
{
	double	rotspeed;

	if (s->key.w)
		ft_move(s, s->dir.x, s->dir.y);
	if (s->key.s)
		ft_move(s, -s->dir.x, -s->dir.y);
	if (s->key.a)
		ft_move(s, -s->pln.x, -s->pln.y);
	if (s->key.d)
		ft_move(s, s->pln.x, s->pln.y);
	rotspeed = 3.0 / 60;
	if (s->key.left)
		ft_rotate(s, -rotspeed);
	if (s->key.right)
		ft_rotate(s, rotspeed);
	return (0);
}
