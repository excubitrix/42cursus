/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 08:22:03 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:04:14 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_health(t_data *s, t_img *tex, int x, int y)
{
	t_vec	size;
	int		clr;

	ft_get_size(s, &size, tex, 4);
	tex->pos.y = (s->win.h - 20 - size.y);
	while (y < size.y)
	{
		x = 0;
		tex->x = 0;
		while (x < size.x)
		{
			if (x < (size.x * s->plr.hp))
			{
				clr = get_pixel(s->tex[HEALTH], tex->x, tex->y);
				clr ? put_pixel(s, x + 12, y + tex->pos.y, clr) : 0;
			}
			clr = get_pixel(s->tex[BAR], tex->x, tex->y);
			clr ? put_pixel(s, x + 12, y + tex->pos.y, clr) : 0;
			tex->x += tex->step.x;
			x++;
		}
		tex->y += tex->step.y;
		y++;
	}
}

void	draw_inventory(t_data *s, t_img *tex, t_inv inv, int y)
{
	t_vec	size;
	int		clr;
	int		x;

	ft_get_size(s, &size, tex, 2.7);
	tex->pos.x = 20 + (s->win.w / 2 - size.x / 2);
	tex->pos.y = (s->win.h - 20 - size.y);
	while (y < size.y)
	{
		x = 0;
		tex->x = 0;
		while (x < size.x)
		{
			if ((clr = get_pixel(s->tex[INVENTORY], tex->x, tex->y)))
				put_pixel(s, x + tex->pos.x, y + tex->pos.y, change_opc(0.6,
					clr, get_pixel(s->img, x + tex->pos.x, y + tex->pos.y)));
			if (isinv(x, size, inv))
				if ((clr = get_pixel(s->tex[ITEMS], tex->x, tex->y)))
					put_pixel(s, x + tex->pos.x, y + tex->pos.y, clr);
			tex->x += tex->step.x;
			x++;
		}
		tex->y += tex->step.y;
		y++;
	}
}

void	draw_energy(t_data *s, t_img *tex, int x, int y)
{
	t_vec	size;
	int		clr;

	ft_get_size(s, &size, tex, 3.2);
	tex->pos.x = (s->win.w - 12 - size.x);
	tex->pos.y = (s->win.h - 20 - size.y);
	while (y < size.y)
	{
		x = 0;
		tex->x = 0;
		while (x < size.x)
		{
			clr = get_pixel(s->tex[COUNTER_BG], tex->x, tex->y);
			clr ? put_pixel(s, x + tex->pos.x, y + tex->pos.y, change_opc(0.6,
				clr, get_pixel(s->img, x + tex->pos.x, y + tex->pos.y))) : 0;
			clr = get_pixel(s->tex[COUNTER], tex->x, tex->y);
			clr ? put_pixel(s, x + tex->pos.x, y + tex->pos.y, clr) : 0;
			clr = get_pixel_img(s, tex->x, tex->y);
			clr ? put_pixel(s, x + tex->pos.x, y + tex->pos.y, clr) : 0;
			tex->x += tex->step.x;
			x++;
		}
		tex->y += tex->step.y;
		y++;
	}
}

void	draw_end(t_data *s, t_img *tex, int x, int y)
{
	t_vec	size;
	int		clr;

	ft_get_size(s, &size, tex, 2);
	draw_hit(s, 0.75, create_trgb(0, 0, 0, 0));
	tex->y = 0;
	while (y < size.y)
	{
		x = 0;
		tex->x = 0;
		while (x < size.x)
		{
			clr = get_pixel(*tex, tex->x, tex->y);
			clr ? put_pixel(s, x + (s->win.w / 2 - size.x / 2),
				y + (s->win.h / 2 - size.y / 2), clr) : 0;
			tex->x += tex->step.x;
			x++;
		}
		tex->y += tex->step.y;
		y++;
	}
}

void	draw_hud(t_data *s)
{
	if (s->plr.old_hp > s->plr.hp)
		draw_hit(s, 0.75, create_trgb(0, 255, 0, 0));
	else
	{
		s->tex[BAR].y = 0;
		draw_health(s, &s->tex[BAR], 0, 0);
		s->tex[INVENTORY].y = 0;
		draw_inventory(s, &s->tex[INVENTORY], s->plr.inv, 0);
		s->tex[COUNTER].y = 0;
		if (s->map.energy)
			draw_energy(s, &s->tex[COUNTER], 0, 0);
	}
	if (s->plr.hp <= DEAD)
		draw_end(s, &s->tex[LOOSE], 0, 0);
	else if (s->plr.hp < CRITICAL)
		draw_flash(s);
	else if (s->plr.energy == 3)
		draw_end(s, &s->tex[WIN], 0, 0);
	s->plr.old_hp = s->plr.hp;
}
