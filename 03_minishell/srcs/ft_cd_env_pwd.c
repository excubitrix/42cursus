/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_env_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 13:04:52 by floogman          #+#    #+#             */
/*   Updated: 2021/03/26 08:32:16 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Puts an error message to the screen.
*/

static void	put_error(char *cmd, char *s, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(s, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(msg, STDERR);
}

/*
** Updates the OLDPWD environment variable.
*/

static void	update_oldpwd(t_info *info, t_cmd *cmd)
{
	char	*old_path;
	char	**tmp;
	int		i;

	if (!(old_path = ft_strjoin("OLDPWD=", info->path)))
		ft_exit(info, cmd);
	if ((i = get_envp(info, "OLDPWD")) >= 0)
	{
		free(info->envp[i]);
		info->envp[i] = old_path;
	}
	else
	{
		if (!(tmp = tab_add(info->envp, old_path)))
			ft_exit(info, NULL);
		info->envp = tmp;
	}
}

/*
** Our build-in cd command. After a successful call to chdir(), update_oldpwd()
** and get_path() are called to keep the OLDPWD and PWD environment variables
** up to date.
*/

int			ft_cd(t_info *info, t_cmd *cmd)
{
	char	*path;

	path = cmd->argv[1];
	if (cmd->argc == 1)
		path = info->home;
	if (chdir(path) != 0)
	{
		put_error("cd", cmd->argv[1], strerror(errno));
		return (FAILURE);
	}
	update_oldpwd(info, cmd);
	return (get_path(info, cmd));
}

/*
** Our build-in env command. It prints the environment variables contained in
** info->envp and takes no arguments.
*/

int			ft_env(t_info *info, t_cmd *cmd)
{
	int		i;

	if (cmd->argc > 1)
	{
		put_error("env", cmd->argv[1], "too many arguments");
		return (NOT_FOUND);
	}
	i = 0;
	while (info->envp[i])
	{
		if (ft_strchr(info->envp[i], '='))
			ft_putendl_fd(info->envp[i], STDOUT);
		i++;
	}
	return (SUCCESS);
}

/*
** Our build-in pwd command. It prints the path to the current directory which
** is being kept up to date by get_path(), called after every cd and stored in
** info->path.
*/

int			ft_pwd(t_info *info, t_cmd *cmd)
{
	(void)cmd;
	ft_putendl_fd(info->path, STDOUT);
	return (SUCCESS);
}
