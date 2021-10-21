/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 08:35:52 by floogman          #+#    #+#             */
/*   Updated: 2021/03/24 13:56:10 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Function that is invoked when ctrl-D is pressed.
*/

void	ctrl_d(t_info *info)
{
	ft_putendl_fd("logout", STDERR);
	ft_exit(info, NULL);
}

/*
** Signal handler for both SIGINT and SIGQUIT signals.
*/

void	sig_handler(int signum)
{
	if (signum == 2 && !g_sig.pid)
		g_sig.exstat = FAILURE;
	if (signum == 2 && g_sig.pid)
	{
		write(STDERR, "\n", 1);
		kill(g_sig.pid, SIGINT);
		g_sig.exstat = 130;
		g_sig.sigint = 1;
		g_sig.pid = 0;
	}
	else if (signum == 3 && g_sig.pid)
	{
		ft_putendl_fd("Quit: 3", STDERR);
		kill(g_sig.pid, SIGQUIT);
		g_sig.exstat = 131;
		g_sig.sigquit = 1;
		g_sig.pid = 0;
	}
}
