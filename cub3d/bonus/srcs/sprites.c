/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 10:11:53 by floogman          #+#    #+#             */
/*   Updated: 2021/01/20 09:22:07 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_sort(int *order, double *tosort, int nbr)
{
	int	i;
	int	j;

	j = 0;
	while (j < nbr)
	{
		i = 0;
		while (i < nbr - 1)
		{
			if (tosort[order[i]] < tosort[order[i + 1]])
				ft_swap(order, i);
			i++;
		}
		j++;
	}
}

void	sort_sprites(t_data *s)
{
	int i;

	i = 0;
	while (i < s->snbr)
	{
		s->sorder[i] = i;
		s->sdst[i] = ((s->plr.pos.x - s->spr[i]->x) *
			(s->plr.pos.x - s->spr[i]->x) + (s->plr.pos.y - s->spr[i]->y)
			* (s->plr.pos.y - s->spr[i]->y));
		i++;
	}
	ft_sort(s->sorder, s->sdst, s->snbr);
}

void	calc_sprite(t_data *s, t_vars *v)
{
	v->invdet = 1.0 / (s->pln.x * s->plr.dir.y - s->plr.dir.x * s->pln.y);
	v->transf.x = v->invdet * (s->plr.dir.y * v->spr.x - s->plr.dir.x
		* v->spr.y);
	v->transf.y = v->invdet * (-s->pln.y * v->spr.x + s->pln.x
		* v->spr.y);
	v->screenx = (int)((s->win.w / 2) * (1 + v->transf.x
		/ v->transf.y));
	v->ver_move = (int)(0.0 / v->transf.y) + s->ray.pitch + s->plr.pos.z
		/ v->transf.y;
	v->h = abs((int)(s->win.h / v->transf.y));
	v->start.y = -(int)v->h / 2 + s->win.h / 2 + v->ver_move;
	if (v->start.y < 0)
		v->start.y = 0;
	v->end.y = (int)v->h / 2 + s->win.h / 2 + v->ver_move;
	if (v->end.y >= s->win.h)
		v->end.y = s->win.h - 1;
	v->w = abs((int)(s->win.h / v->transf.y));
	v->start.x = -(int)v->w / 2 + v->screenx;
	if (v->start.x < 0)
		v->start.x = 0;
	v->end.x = (int)v->w / 2 + v->screenx;
	if (v->end.x >= s->win.w)
		v->end.x = s->win.w - 1;
}

void	draw_sprite(t_data *s, t_vars v, int nbr, t_xy start)
{
	t_xy	spr;
	int		clr;

	while (start.x < v.end.x)
	{
		spr.x = (int)(256 * (start.x - (-v.w / 2 + v.screenx)) * s->tex[nbr].h
			/ v.w) / 256;
		if (v.transf.y > 0 && start.x > 0 && start.x < s->win.w
			&& v.transf.y < s->zbuffer[start.x])
		{
			start.y = v.start.y;
			while (start.y < v.end.y)
			{
				spr.y = ((((start.y - v.ver_move) * 256 - s->win.h * 128 + v.h
					* 128) * s->tex[nbr].h) / v.h) / 256;
				clr = get_pixel(s->tex[nbr], spr.x, spr.y);
				if (clr != 0)
					put_pixel(s, start.x, start.y, add_shadow((9 - v.transf.y)
					/ 9 < 0 ? 0.01 : (9 - v.transf.y) / 9, clr));
				start.y++;
			}
		}
		start.x++;
	}
}

void	cast_sprites(t_data *s, int i)
{
	t_xy	start;

	sort_sprites(s);
	while (i < s->snbr)
	{
		if (!s->spr[s->sorder[i]]->door)
		{
			s->v.spr.x = s->spr[s->sorder[i]]->x - s->plr.pos.x;
			s->v.spr.y = s->spr[s->sorder[i]]->y - s->plr.pos.y;
			calc_sprite(s, &s->v);
			start.x = s->v.start.x;
			start.y = s->v.start.y;
			draw_sprite(s, s->v, s->spr[s->sorder[i]]->tex, start);
		}
		i++;
	}
}
