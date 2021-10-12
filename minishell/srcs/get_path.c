/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:53:13 by floogman          #+#    #+#             */
/*   Updated: 2021/03/26 09:34:38 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Sets the prompt used by print_prompt() to the current directory and updates
** the length of the prompt.
*/

void		set_prompt(t_info *info)
{
	char	*prompt;

	if (info->trm_ptr->initialised)
	{
		if (ft_strcmp(info->path, "/"))
		{
			prompt = ft_strrchr(info->path, '/');
			prompt++;
		}
		else
			prompt = info->path;
		info->trm_ptr->prompt = prompt;
		info->trm_ptr->prompt_len = ft_strlen(prompt) + 4;
	}
}

/*
** Prints an error message to the screen and concatenates '/.' to the current
** path if 'cd .' was performed in a deleted directory.
*/

static int	put_error(t_info *info, t_cmd *cmd, char *tmp, int i)
{
	ft_putstr_fd("minishell: cd: ", STDERR);
	if ((!ft_strcmp(cmd->argv[1], ".")))
	{
		if (!(info->path = ft_realloc(tmp, ft_strlen(info->path) + 3)))
			ft_exit(info, cmd);
		ft_strcat(info->path, "/.");
		if ((i = tab_stristr(info->envp, "PWD=")) >= 0)
		{
			if (!(tmp = ft_strjoin("PWD=", info->path)))
				ft_exit(info, cmd);
			free(info->envp[i]);
			info->envp[i] = tmp;
		}
		set_prompt(info);
	}
	else
	{
		free(tmp);
		ft_putstr_fd(cmd->argv[1], STDERR);
		ft_putchar_fd(' ', STDERR);
	}
	ft_putendl_fd(strerror(errno), STDERR);
	return (FAILURE);
}

/*
** Retrieves the current directory by calling getcwd(), updates the PWD
** environment variable accordingly and calls set_prompt() to keep the prompt
** used by print_prompt() up to date.
** NOTE: If getcwd() is called with NULL as its first parameter, size
** is ignored and space is allocated as needed to store the pathname.
*/

int			get_path(t_info *info, t_cmd *cmd)
{
	char	*tmp;
	int		i;

	tmp = info->path;
	info->path = NULL;
	if (!(info->path = getcwd(info->path, 0)))
	{
		if (!cmd)
			return (FAILURE);
		return (put_error(info, cmd, tmp, 0));
	}
	if (tmp)
		free(tmp);
	if (!(tmp = ft_strjoin("PWD=", info->path)))
		ft_exit(info, cmd);
	if ((i = tab_stristr(info->envp, "PWD=")) >= 0)
	{
		free(info->envp[i]);
		info->envp[i] = tmp;
	}
	else if (!(info->envp = tab_add_free(info->envp, tmp)))
		ft_exit(info, cmd);
	set_prompt(info);
	return (SUCCESS);
}
