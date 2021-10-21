/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_plr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 13:58:03 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:04:27 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	save_pos(t_data *s, int i, int nbr)
{
	if (s->map.plr)
	{
		s->ln = s->map.h + 1;
		s->col = i + 1;
		ft_abort(s, 15, __FILE__, __LINE__);
	}
	init_plr(s, nbr, i + 0.5, s->map.h + 0.5);
	s->map.plr = 1;
}

void	init_plr(t_data *s, int nbr, double x, double y)
{
	t_inv	inv;
	t_vec	pos;

	inv.i = 0;
	inv.ii = 0;
	inv.iii = 0;
	inv.iv = 0;
	s->plr.inv = inv;
	pos.x = x;
	pos.y = y;
	pos.z = 0;
	s->plr.pos = pos;
	s->plr.hp = FULL;
	s->plr.old_hp = s->plr.hp;
	s->plr.energy = 0;
	set_dir(s, nbr);
}

void	set_dir(t_data *s, int nbr)
{
	t_vec	dir;

	if (nbr == 0)
		dir.y = -1;
	if (nbr == 1)
		dir.y = 1;
	if (nbr == 2)
		dir.x = -1;
	if (nbr == 3)
		dir.x = 1;
	s->plr.dir = dir;
	set_pln(s, nbr);
}

void	set_pln(t_data *s, int nbr)
{
	t_vec	pln;

	s->scaler = (double)s->win.h / (double)s->win.w;
	if (nbr == 0)
		pln.x = (0.66 / s->scaler);
	if (nbr == 1)
		pln.x = -(0.66 / s->scaler);
	if (nbr == 2)
		pln.y = -(0.66 / s->scaler);
	if (nbr == 3)
		pln.y = (0.66 / s->scaler);
	s->pln = pln;
}
