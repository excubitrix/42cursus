/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:30:10 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:05:11 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_data *s, char *path, int nbr)
{
	if (!(s->tex[nbr].ptr = mlx_xpm_file_to_image(s->mlx, path,
		&s->tex[nbr].w, &s->tex[nbr].h))
		|| !(s->tex[nbr].addr = mlx_get_data_addr(s->tex[nbr].ptr,
		&s->tex[nbr].bpp, &s->tex[nbr].ll, &s->tex[nbr].endian)))
		ft_abort(s, 0, __FILE__, __LINE__);
}

void	load_door_tex(t_data *s)
{
	load_texture(s, "./bonus/imgs/door/frame1.xpm", DOOR);
	load_texture(s, "./bonus/imgs/door/frame2.xpm", DOOR + 1);
	load_texture(s, "./bonus/imgs/door/frame3.xpm", DOOR + 2);
	load_texture(s, "./bonus/imgs/door/frame4.xpm", DOOR + 3);
	load_texture(s, "./bonus/imgs/door/frame5.xpm", DOOR + 4);
	load_texture(s, "./bonus/imgs/door/bloody1.xpm", DOOR + 5);
	load_texture(s, "./bonus/imgs/door/bloody2.xpm", DOOR + 6);
	load_texture(s, "./bonus/imgs/door/bloody3.xpm", DOOR + 7);
	load_texture(s, "./bonus/imgs/door/bloody4.xpm", DOOR + 8);
	load_texture(s, "./bonus/imgs/door/bloody5.xpm", DOOR + 9);
}

void	load_imgs(t_data *s)
{
	int		i;

	i = -1;
	while (++i < DOOR)
		load_texture(s, s->tex[i].path, i);
	load_door_tex(s);
	load_texture(s, "./bonus/imgs/hud/bar.xpm", BAR);
	load_texture(s, "./bonus/imgs/hud/health.xpm", HEALTH);
	load_texture(s, "./bonus/imgs/hud/inventory.xpm", INVENTORY);
	load_texture(s, "./bonus/imgs/hud/items.xpm", ITEMS);
	load_texture(s, "./bonus/imgs/hud/zero.xpm", ZERO);
	load_texture(s, "./bonus/imgs/hud/one.xpm", ONE);
	load_texture(s, "./bonus/imgs/hud/two.xpm", TWO);
	load_texture(s, "./bonus/imgs/hud/three.xpm", THREE);
	load_texture(s, "./bonus/imgs/hud/counter.xpm", COUNTER);
	load_texture(s, "./bonus/imgs/hud/counter_bg.xpm", COUNTER_BG);
	load_texture(s, "./bonus/imgs/other/loose.xpm", LOOSE);
	load_texture(s, "./bonus/imgs/other/win.xpm", WIN);
	load_texture(s, "./bonus/imgs/other/black.xpm", EMPTY);
}
