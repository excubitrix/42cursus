/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:03:26 by floogman          #+#    #+#             */
/*   Updated: 2021/01/23 20:05:35 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_close(t_data *s, int open, double diff, int i)
{
	if (open)
	{
		if (diff > 0.2)
			s->spr[i]->tex = s->door[s->spr[i]->bldy][3];
		else if (diff > 0.1)
			s->spr[i]->tex = s->door[s->spr[i]->bldy][2];
		else
			s->spr[i]->tex = s->door[s->spr[i]->bldy][1];
	}
	else
	{
		if (diff > 0.2)
			s->spr[i]->tex = s->door[s->spr[i]->bldy][1];
		else if (diff > 0.1)
			s->spr[i]->tex = s->door[s->spr[i]->bldy][2];
		else
			s->spr[i]->tex = s->door[s->spr[i]->bldy][3];
	}
}

void	door_animation(t_data *s, double time, int i)
{
	double	diff;
	int		open;
	int		step;

	open = s->spr[i]->open;
	step = open ? 1 : -1;
	diff = (time - s->spr[i]->t) / CLOCKS_PER_SEC;
	if (diff > 0.3)
	{
		s->spr[i]->tex = !open ? s->door[s->spr[i]->bldy][0]
		: s->door[s->spr[i]->bldy][4];
		s->spr[i]->t = 0;
		s->spr[i]->tt = !open ? 0 : clock();
		return ;
	}
	else
		open_close(s, open, diff, i);
}

void	automated_close(t_data *s, t_spr *spr, t_plr *plr, int *hit)
{
	char	c;

	spr->t = clock();
	c = get_tile(s, spr->x, spr->y);
	if ((int)plr->pos.x != (int)spr->x || (int)plr->pos.y != (int)spr->y)
	{
		set_tile(s, spr->x, spr->y, c - 32);
		!*hit ? system("afplay -v 0.2 ./bonus/sound/close.mp3 & exit") : 0;
		spr->tt = 0;
		*hit = 0;
	}
	else if (spr->trap && !*hit)
	{
		system("afplay -v 0.2 ./bonus/sound/close.mp3 & exit");
		plr->hp = (plr->hp -= 0.085) < DEAD ? DEAD : plr->hp - 0.085;
		s->last_start_beat = (plr->hp < CRITICAL) ? clock() : 0;
		s->game_over = (plr->hp <= DEAD) ? 1 : s->game_over;
		spr->tex = s->door[1][2];
		spr->bldy = 1;
		(s->game_over) ? ft_printf(BLACK"You were snapped in half by the door."
			"\nPress [esc] to exit.\n"RE) : ft_printf(BLUE"Aargh! "BLACK
			"The door tried to close with you in it.\n"RE);
		*hit = 1;
	}
}

void	doors(t_data *s, double time)
{
	double		diff;
	int			i;

	i = 0;
	while (i < s->snbr)
	{
		if (s->spr[i]->t)
			door_animation(s, time, i);
		if (s->spr[i]->tt)
		{
			s->spr[i]->open = 0;
			diff = (time - s->spr[i]->tt) / CLOCKS_PER_SEC;
			if ((!s->spr[i]->trap && diff > 2)
				|| (s->spr[i]->trap && diff > 0.2))
				automated_close(s, s->spr[i], &s->plr, &s->spr[i]->hit);
		}
		i++;
	}
}

void	init_door(t_data *s)
{
	s->door[0][0] = DOOR;
	s->door[0][1] = DOOR + 1;
	s->door[0][2] = DOOR + 2;
	s->door[0][3] = DOOR + 3;
	s->door[0][4] = DOOR + 4;
	s->door[1][0] = DOOR + 5;
	s->door[1][1] = DOOR + 6;
	s->door[1][2] = DOOR + 7;
	s->door[1][3] = DOOR + 8;
	s->door[1][4] = DOOR + 9;
}
