/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 13:28:34 by floogman          #+#    #+#             */
/*   Updated: 2021/01/18 08:25:08 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_kpress(int keycode, t_data *s)
{
	if (keycode == KEY_ESC)
		ft_exit(s);
	if (keycode == KEY_W)
		s->key.w = 1;
	if (keycode == KEY_A)
		s->key.a = 1;
	if (keycode == KEY_S)
		s->key.s = 1;
	if (keycode == KEY_D)
		s->key.d = 1;
	if (keycode == KEY_RIGHT)
		s->key.right = 1;
	if (keycode == KEY_LEFT)
		s->key.left = 1;
	return (0);
}

int		ft_krelease(int keycode, t_data *s)
{
	if (keycode == KEY_W)
		s->key.w = 0;
	if (keycode == KEY_A)
		s->key.a = 0;
	if (keycode == KEY_S)
		s->key.s = 0;
	if (keycode == KEY_D)
		s->key.d = 0;
	if (keycode == KEY_RIGHT)
		s->key.right = 0;
	if (keycode == KEY_LEFT)
		s->key.left = 0;
	return (0);
}

int		render_frame(t_data *s)
{
	cast_walls(s);
	cast_sprites(s);
	mlx_put_image_to_window(s->mlx, s->win.ptr, s->img.ptr, 0, 0);
	movement(s);
	return (0);
}
