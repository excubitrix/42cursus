/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 08:24:58 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:06:46 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sound(t_data *s)
{
	s->sound = 1;
	s->last_start_beat = 0;
	s->last_start_song = clock();
	// system("afplay -v 0.1 ./bonus/sound/maintheme.mp3 & exit");
	system("afplay -v 0.3 ./bonus/sound/maintheme.mp3 & exit");
}

void	play_music(t_data *s)
{
	static int	crit;

	if ((double)(s->time.x - s->last_start_song)
		/ (double)CLOCKS_PER_SEC >= 93.5)
	{
		system("killall afplay");
		// system("afplay -v 0.1 ./bonus/sound/maintheme.mp3 & exit");
		system("afplay -v 0.3 ./bonus/sound/maintheme.mp3 & exit");
		s->last_start_song = s->time.x;
		crit = 0;
	}
	if (s->plr.hp < CRITICAL && (!crit || (double)(s->time.x
		- s->last_start_beat) / (double)CLOCKS_PER_SEC >= 29.5))
	{
		system("afplay ./bonus/sound/heartbeat.mp3 & exit");
		s->last_start_beat = s->time.x;
		crit = 1;
	}
	else if (s->plr.hp > CRITICAL && crit)
	{
		system("killall afplay");
		init_sound(s);
		crit = 0;
	}
}
