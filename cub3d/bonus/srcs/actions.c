/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:08:54 by floogman          #+#    #+#             */
/*   Updated: 2021/01/23 15:18:41 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_open_close(t_data *s, double var, int x)
{
	t_vec	pos;
	int		nbr;
	char	plr;
	char	c;

	pos.x = x ? s->plr.pos.x + var : s->plr.pos.x;
	pos.y = !x ? s->plr.pos.y + var : s->plr.pos.y;
	c = get_tile(s, pos.x, pos.y);
	nbr = get_snbr(s, pos.x, pos.y);
	plr = get_tile(s, s->plr.pos.x, s->plr.pos.y);
	if (c == 'I' || c == 'H')
	{
		set_tile(s, pos.x, pos.y, c + 32);
		s->spr[nbr]->open = 1;
		s->spr[nbr]->t = clock();
		system("afplay -v 0.2 ./bonus/sound/open.wav & exit");
	}
	else if ((c == 'i' || c == 'h') && (plr != 'i' && plr != 'h')
		&& !s->spr[nbr]->trap)
	{
		set_tile(s, pos.x, pos.y, c - 32);
		s->spr[nbr]->open = 0;
		s->spr[nbr]->t = clock();
		system("afplay -v 0.2 ./bonus/sound/close.mp3 & exit");
	}
}

void	ft_pick_up(t_data *s, t_plr *plr, double var, int x)
{
	t_vec	pos;
	int		nbr;
	char	c;

	pos.x = x ? plr->pos.x + var : plr->pos.x;
	pos.y = !x ? plr->pos.y + var : plr->pos.y;
	c = get_tile(s, pos.x, pos.y);
	nbr = get_snbr(s, pos.x, pos.y);
	if (c == '5' && plr->hp == FULL)
		(!checkin_inv(&plr->inv)) &&
			ft_printf(BLACK"You don't have enough space in your bag.\n"RE);
	if (((c == '5' && (!plr->inv.i || !plr->inv.ii || !plr->inv.iii ||
		!plr->inv.iv || plr->hp < FULL)) || (c == '4' && plr->energy < 3)))
	{
		s->spr[nbr]->tex = EMPTY;
		set_tile(s, (int)s->spr[nbr]->x, (int)s->spr[nbr]->y, '0');
		if (c == '5')
			heal(s);
		else
			take(s);
	}
	s->game_over = (s->plr.energy == 3) ? 1 : 0;
	if (s->game_over)
		ft_printf(BLACK"Press [esc] to exit.\n"RE);
}

void	ft_use_item(t_data *s, t_inv *inv, int nbr)
{
	if (s->plr.hp < FULL)
	{
		if ((nbr == 1 && inv->i == 1) || (nbr == 2 && inv->ii == 1)
			|| (nbr == 3 && inv->iii == 1) || (nbr == 4 && inv->iv == 1))
			heal(s);
	}
	else if ((nbr == 1 && inv->i == 1) || (nbr == 2 && inv->ii == 1)
		|| (nbr == 3 && inv->iii == 1) || (nbr == 4 && inv->iv == 1))
		ft_printf(BLACK"You don't feel like chicken noodles right now.\n"RE);
}
