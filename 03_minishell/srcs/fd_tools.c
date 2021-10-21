/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 09:45:59 by floogman          #+#    #+#             */
/*   Updated: 2021/03/24 13:53:21 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Closes the fd passed if it has a valid value.
*/

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

/*
** Restores info->in and info->out to STDIN (0) and STDOUT (1)
** respectively.
*/

void	restore_std(t_info *info)
{
	dup2(info->in, STDIN);
	dup2(info->out, STDOUT);
}

/*
** Closes any redirection and pipe fds that remain open.
*/

void	close_fds(t_info *info)
{
	ft_close(info->fd_in);
	ft_close(info->fd_out);
	ft_close(info->pipe_in);
	ft_close(info->pipe_out);
}

/*
** Sets all redirection and pipe fds to invalid values. It is
** used to initialize the fds and also called after each call
** to close_fd().
*/

void	reset_fds(t_info *info)
{
	info->fd_in = -1;
	info->fd_out = -1;
	info->pipe_in = -1;
	info->pipe_out = -1;
}
