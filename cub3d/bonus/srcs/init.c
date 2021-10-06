/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:23:56 by floogman          #+#    #+#             */
/*   Updated: 2021/01/23 20:03:27 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_data *s, int bmp)
{
	s->mlx = mlx_init();
	load_imgs(s);
	if (!bmp)
	{
		s->time.x = 0;
		s->time.z = 0;
		s->win.ptr = mlx_new_window(s->mlx, s->win.w, s->win.h,
			"cub3D: My first RayCaster with miniLibX");
		mlx_mouse_hide();
		mlx_mouse_move(s->win.ptr, 0, 0);
		init_sound(s);
	}
	s->img.ptr = mlx_new_image(s->mlx, s->win.w, s->win.h);
	s->img.addr = mlx_get_data_addr(s->img.ptr, &s->img.bpp, &s->img.ll,
		&s->img.endian);
	if (!(s->sorder = malloc(sizeof(int) * s->snbr))
		|| !(s->sdst = malloc(sizeof(double) * s->snbr))
		|| !(s->zbuffer = malloc(sizeof(double) * s->win.w)))
		ft_abort(s, 0, __FILE__, __LINE__);
}

void	init_spr(t_data *s, int i, int nbr, t_vec pos)
{
	t_spr	*spr;

	if (!(spr = malloc(sizeof(t_spr))))
		ft_abort(s, 0, __FILE__, __LINE__);
	spr->trap = 0;
	if (nbr == 10)
	{
		nbr++;
		spr->trap = 1;
	}
	else if (nbr == 8)
		s->map.energy++;
	spr->tex = nbr;
	spr->door = (nbr == DOOR) ? 1 : 0;
	spr->hit = 0;
	spr->open = 0;
	spr->bldy = 0;
	spr->x = pos.x + 0.5;
	spr->y = pos.y + 0.5;
	spr->t = 0;
	spr->tt = 0;
	s->spr[i] = spr;
}

void	init_tex(t_data *s)
{
	t_img	tex;
	int		i;

	tex.ptr = NULL;
	tex.addr = NULL;
	tex.path = NULL;
	tex.w = 0;
	tex.h = 0;
	tex.x = 0;
	tex.y = 0;
	i = -1;
	while (++i < TEXNUM)
		s->tex[i] = tex;
}

void	init_map_and_key(t_data *s)
{
	t_map	map;
	t_key	key;

	map.ptr = NULL;
	map.w = 0;
	map.h = 0;
	map.x = 0;
	map.y = 0;
	map.plr = 0;
	map.energy = 0;
	map.parsing = 0;
	s->map = map;
	key.a = 0;
	key.s = 0;
	key.d = 0;
	key.w = 0;
	key.shift = 0;
	key.left = 0;
	key.right = 0;
	key.down = 0;
	key.up = 0;
	key.space = 0;
	key.e = 0;
	key.jump = 0;
	s->key = key;
}

void	init_s(t_data *s)
{
	t_win	win;
	t_img	img;

	s->line = NULL;
	s->ln = 0;
	s->col = 0;
	win.ptr = NULL;
	win.w = 0;
	win.h = 0;
	s->win = win;
	img.ptr = NULL;
	img.addr = NULL;
	s->img = img;
	init_tex(s);
	s->spr = NULL;
	init_door(s);
	s->snbr = 0;
	s->elem = 0;
	init_map_and_key(s);
	s->ray.pitch = 0;
	s->sound = 0;
	s->game_over = 0;
	init_errmsg(s);
}
