/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 08:35:10 by floogman          #+#    #+#             */
/*   Updated: 2021/03/24 13:34:06 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Puts an error message to the screen.
*/

static void	put_error(t_info *info, char *file)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(file, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(strerror(errno), STDERR);
	info->ret = 1;
	info->error = 1;
}

/*
** Opens a file for reading.
*/

int			open_file_in(t_info *info, char *file)
{
	ft_close(info->fd_in);
	if ((info->fd_in = open(file, O_RDONLY)) < 0)
	{
		put_error(info, file);
		return (-1);
	}
	dup2(info->fd_in, STDIN);
	return (SUCCESS);
}

/*
** Opens a file for writing.
*/

int			open_file_out(t_info *info, char *file, int append)
{
	ft_close(info->fd_out);
	if (append)
		info->fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		info->fd_out = open(file, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (info->fd_out == -1)
	{
		put_error(info, file);
		return (-1);
	}
	else if (info->fd)
	{
		if (info->fd > FDCAP && check_fd_stat(info->fd) != 0)
		{
			put_error(info, file);
			return (-1);
		}
		dup2(info->fd_out, info->fd);
	}
	else
		dup2(info->fd_out, STDOUT);
	return (SUCCESS);
}
