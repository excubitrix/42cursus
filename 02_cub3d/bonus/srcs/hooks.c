/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 13:28:34 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:03:48 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_kpress(int keycode, t_data *s)
{
	(keycode == KEY_ESC) ? ft_exit(s) : 0;
	(keycode == KEY_W) ? s->key.w = 1 : 0;
	(keycode == KEY_A) ? s->key.a = 1 : 0;
	(keycode == KEY_S) ? s->key.s = 1 : 0;
	(keycode == KEY_D) ? s->key.d = 1 : 0;
	if (keycode == KEY_E)
		do_action(s, s->plr, s->pln);
	(keycode == KEY_ONE) ? ft_use_item(s, &s->plr.inv, 1) : 0;
	(keycode == KEY_TWO) ? ft_use_item(s, &s->plr.inv, 2) : 0;
	(keycode == KEY_THREE) ? ft_use_item(s, &s->plr.inv, 3) : 0;
	(keycode == KEY_FOUR) ? ft_use_item(s, &s->plr.inv, 4) : 0;
	(keycode == KEY_SPACE && !s->key.space && !s->key.jump && !s->key.shift
		&& (s->plr.hp > CRITICAL)) ? jumping(s, 1, 0) : 0;
	(keycode == KEY_SHIFT && !s->key.jump) ? s->key.shift = 1 : 0;
	(keycode == KEY_RIGHT) ? s->key.right = 1 : 0;
	(keycode == KEY_LEFT) ? s->key.left = 1 : 0;
	(keycode == KEY_UP) ? s->key.up = 1 : 0;
	(keycode == KEY_DOWN) ? s->key.down = 1 : 0;
	return (0);
}

int		ft_krelease(int keycode, t_data *s)
{
	(keycode == KEY_W) ? s->key.w = 0 : 0;
	(keycode == KEY_A) ? s->key.a = 0 : 0;
	(keycode == KEY_S) ? s->key.s = 0 : 0;
	(keycode == KEY_D) ? s->key.d = 0 : 0;
	(keycode == KEY_SPACE) ? s->key.space = 0 : 0;
	if (keycode == KEY_SHIFT)
	{
		s->plr.pos.z = 0;
		s->key.shift = 0;
	}
	(keycode == KEY_RIGHT) ? s->key.right = 0 : 0;
	(keycode == KEY_LEFT) ? s->key.left = 0 : 0;
	(keycode == KEY_UP) ? s->key.up = 0 : 0;
	(keycode == KEY_DOWN) ? s->key.down = 0 : 0;
	return (0);
}

int		ft_mouse(int x, int y, t_data *s)
{
	static int	oldx;
	static int	oldy;

	if (!s->game_over)
	{
		if (x - oldx > 1)
			ft_rotate(s, s->time.y * 2.5);
		if (x - oldx < -1)
			ft_rotate(s, -(s->time.y * 2.5));
		if (y - oldy > 1)
			change_pitch(s, 0, s->time.y * 3.0);
		if (y - oldy < -1)
			change_pitch(s, 1, s->time.y * 3.0);
		if (x > s->win.w || x < 0 || y > s->win.h || y < 0)
			mlx_mouse_move(s->win.ptr, s->win.w / 2, s->win.h / 2);
		mlx_mouse_get_pos(s->win.ptr, &oldx, &oldy);
	}
	return (0);
}

void	handle_movement(t_data *s)
{
	if (s->plr.hp < CRITICAL)
		movement(s, s->time.y * 2.5, s->time.y * 0.7);
	else if (s->key.shift)
		movement(s, s->time.y * 2.5, s->time.y * 1.0);
	else
		movement(s, s->time.y * 2.5, s->time.y * 2.0);
}

int		render_frame(t_data *s)
{
	cast_floor(s, 0);
	cast_walls(s, 0);
	cast_sprites(s, 0);
	draw_hud(s);
	mlx_put_image_to_window(s->mlx, s->win.ptr, s->img.ptr, 0, 0);
	s->time.z = s->time.x;
	s->time.x = clock();
	s->time.y = (s->time.x - s->time.z) / CLOCKS_PER_SEC;
	if (!s->game_over)
	{
		handle_movement(s);
		if (s->plr.pos.z && !s->key.shift)
			jumping(s, 0, s->time.y * 2.5);
		doors(s, s->time.x);
		play_music(s);
	}
	else if (s->sound)
	{
		system("killall afplay");
		s->sound = 0;
	}
	return (0);
}
