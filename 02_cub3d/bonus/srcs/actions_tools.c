/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:09:27 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 08:59:17 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	take(t_data *s)
{
	ft_printf(BLUE"This looks useful. "BLACK"You take it.\n"RE);
	s->plr.energy++;
}

void	heal(t_data *s)
{
	if (s->plr.hp < FULL)
		ft_printf(BLUE"*Slurp* ... "BLACK"You feel better.\n"RE);
	s->plr.hp = s->plr.hp + (FULL / 8) >= FULL ? FULL
	: s->plr.hp + (FULL / 8);
}

int		checkin_inv(t_data *s)
{
	if (!s->plr.inv.i)
		s->plr.inv.i = 1;
	else if (!s->plr.inv.ii)
		s->plr.inv.ii = 1;
	else if (!s->plr.inv.iii)
		s->plr.inv.iii = 1;
	else if (!s->plr.inv.iv)
		s->plr.inv.iv = 1;
	else
		return (0);
	ft_printf(BLACK"You stuff the box of instant noodles into your bag.\n"RE);
	return (1);
}

void	checkout_inv(t_data *s, int nbr)
{
	if (s->plr.inv.i && nbr == 1)
		s->plr.inv.i = 0;
	else if (s->plr.inv.ii && nbr == 2)
		s->plr.inv.ii = 0;
	else if (s->plr.inv.iii && nbr == 3)
		s->plr.inv.iii = 0;
	else if (s->plr.inv.iv && nbr == 4)
		s->plr.inv.iv = 0;
}

void	do_action(t_data *s, t_plr plr, t_vec pln)
{
	if ((plr.dir.x < plr.dir.y && pln.x < pln.y)
		|| (plr.dir.x > plr.dir.y && pln.x > pln.y))
	{
		ft_open_close(s, plr.dir.y, 0);
		ft_pick_up(s, &plr, plr.dir.y, 0);
	}
	else
	{
		ft_open_close(s, plr.dir.x, 1);
		ft_pick_up(s, &plr, plr.dir.x, 1);
	}
}
