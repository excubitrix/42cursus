/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 10:11:53 by floogman          #+#    #+#             */
/*   Updated: 2021/01/18 08:37:15 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_sort(int *order, double *tosort, int nbr)
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
	return (0);
}

int		sort_sprites(t_data *s)
{
	int i;

	i = 0;
	while (i < s->snbr)
	{
		s->sorder[i] = i;
		s->sdst[i] = ((s->pos.x - s->spr[i]->x) * (s->pos.x - s->spr[i]->x)
			+ (s->pos.y - s->spr[i]->y) * (s->pos.y - s->spr[i]->y));
		i++;
	}
	ft_sort(s->sorder, s->sdst, s->snbr);
	return (0);
}

int		calc_sprite(t_data *s, t_vars *v)
{
	v->invdet = 1.0 / (s->pln.x * s->dir.y - s->dir.x * s->pln.y);
	v->transf.x = v->invdet * (s->dir.y * v->spr.x - s->dir.x
		* v->spr.y);
	v->transf.y = v->invdet * (-s->pln.y * v->spr.x + s->pln.x
		* v->spr.y);
	v->screenx = (int)((s->win.w / 2) * (1 + v->transf.x
		/ v->transf.y));
	v->h = abs((int)(s->win.h / v->transf.y));
	v->start.y = -v->h / 2 + s->win.h / 2;
	if (v->start.y < 0)
		v->start.y = 0;
	v->end.y = v->h / 2 + s->win.h / 2;
	if (v->end.y >= s->win.h)
		v->end.y = s->win.h - 1;
	v->w = abs((int)(s->win.h / v->transf.y));
	v->start.x = -v->w / 2 + v->screenx;
	if (v->start.x < 0)
		v->start.x = 0;
	v->end.x = v->w / 2 + v->screenx;
	if (v->end.x >= s->win.w)
		v->end.x = s->win.w - 1;
	return (0);
}

int		draw_sprite(t_data *s, t_vars v, int x, int y)
{
	t_xy	spr;
	int		clr;
	int		d;

	while (x < v.end.x)
	{
		spr.x = (int)(256 * (x - (-v.w / 2 + v.screenx))
			* s->tex[4].h / v.w) / 256;
		if (v.transf.y > 0 && x > 0 && x < s->win.w
			&& v.transf.y < s->zbuffer[x])
		{
			y = v.start.y;
			while (y < v.end.y)
			{
				d = y * 256 - s->win.h * 128 + v.h * 128;
				spr.y = ((d * s->tex[4].h) / v.h) / 256;
				clr = get_pixel(s->tex[4], spr.x, spr.y);
				if (clr != 0)
					put_pixel(s, x, y, clr);
				y++;
			}
		}
		x++;
	}
	return (0);
}

int		cast_sprites(t_data *s)
{
	int		i;

	i = 0;
	sort_sprites(s);
	while (i < s->snbr)
	{
		s->v.spr.x = s->spr[s->sorder[i]]->x - s->pos.x;
		s->v.spr.y = s->spr[s->sorder[i]]->y - s->pos.y;
		calc_sprite(s, &s->v);
		draw_sprite(s, s->v, s->v.start.x, s->v.start.y);
		i++;
	}
	return (0);
}
