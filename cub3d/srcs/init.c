/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:23:56 by floogman          #+#    #+#             */
/*   Updated: 2021/01/18 08:33:41 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_data *s, int bmp)
{
	s->mlx = mlx_init();
	load_textures(s);
	if (!bmp)
		s->win.ptr = mlx_new_window(s->mlx, s->win.w, s->win.h,
			"cub3D: My first RayCaster with miniLibX");
	s->img.ptr = mlx_new_image(s->mlx, s->win.w, s->win.h);
	s->img.addr = mlx_get_data_addr(s->img.ptr, &s->img.bpp, &s->img.ll,
		&s->img.endian);
	if (!(s->sorder = malloc(sizeof(int) * s->snbr))
		|| !(s->sdst = malloc(sizeof(double) * s->snbr))
		|| !(s->zbuffer = malloc(sizeof(double) * s->win.w)))
		ft_abort(s, 0, __FILE__, __LINE__);
}

void	init_spr(t_data *s, int i, int x, int y)
{
	t_vec	*spr;

	if (!(spr = malloc(sizeof(t_vec))))
		ft_abort(s, 0, __FILE__, __LINE__);
	spr->x = x + 0.5;
	spr->y = y + 0.5;
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
	tex.x = 0.0;
	tex.y = 0.0;
	tex.step = 0.0;
	tex.pos = 0.0;
	i = -1;
	while (++i < 5)
		s->tex[i] = tex;
}

void	init_map(t_data *s)
{
	t_map	map;
	t_key	key;

	map.ptr = NULL;
	map.w = 0;
	map.h = 2;
	map.x = 0;
	map.y = 0;
	map.plr = 0;
	map.parsing = 0;
	s->map = map;
	key.a = 0;
	key.s = 0;
	key.d = 0;
	key.w = 0;
	key.left = 0;
	key.right = 0;
	s->key = key;
}

void	init_s(t_data *s)
{
	t_win	win;
	t_img	img;
	t_vars	v;

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
	v.pwd = 0;
	s->v = v;
	init_map(s);
	s->spr = NULL;
	s->snbr = 0;
	s->sorder = NULL;
	s->sdst = NULL;
	s->elem = 0;
	s->zbuffer = NULL;
	init_errmsg(s);
}
