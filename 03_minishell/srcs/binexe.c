/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binexe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 14:43:20 by floogman          #+#    #+#             */
/*   Updated: 2021/03/26 18:55:00 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** In case of execve failing, put_error() checks path and puts a matching error
** message to the screen.
*/

static int	put_error(char *path)
{
	DIR		*dir;
	int		fd;
	int		ret;

	fd = open(path, O_WRONLY);
	dir = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd < 0 && !dir)
		ft_putendl_fd(": No such file or directory", STDERR);
	else if (fd < 0 && dir)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && !dir)
		ft_putendl_fd(": Permission denied", STDERR);
	ret = 0;
	if (!ft_strchr(path, '/') || (fd < 0 && !dir))
		ret = NOT_FOUND;
	else if (fd < 0)
		ret = DIRECTORY;
	if (dir)
		closedir(dir);
	ft_close(fd);
	return (ret);
}

/*
** On success, our forked process is replaced by a process of the command
** pointed to by path.
*/

int			launch(t_info *info, t_cmd *cmd, char *path, char **args)
{
	int		ret;

	ret = SUCCESS;
	if (!(g_sig.pid = fork()))
	{
		if ((execve(path, args, info->envp)) < 0)
			ret = put_error(path);
		free_all(info, cmd, -1);
		exit(ret);
	}
	else
		waitpid(g_sig.pid, &ret, 0);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.exstat);
	ret = WEXITSTATUS(ret);
	return (ret);
}

/*
** Looks for entires with the same name as the command pointed to by char *cmd
** in the directory pointed to by DIR *dir and returns a string containing the
** absolute path if successful otherwise NULL is returned.
*/

char		*check_dir(char *bin, char *cmd)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*path;
	char			*tmp;

	path = NULL;
	if (!(dir = opendir(bin)))
		return (NULL);
	while ((entry = readdir(dir)))
	{
		if (!ft_strcmp(entry->d_name, cmd))
		{
			tmp = ft_strjoin(bin, "/");
			path = ft_strjoin(tmp, entry->d_name);
			free(tmp);
			break ;
		}
	}
	closedir(dir);
	return (path);
}

/*
** Sets the _ environment variable to the absulte path of the process about to
** be executed if present.
*/

void		set__(t_info *info, t_cmd *cmd, char *path)
{
	char	**temp;
	char	*tmp;
	int		i;

	if (!path)
		tab_delone(info->envp, "_=");
	if ((i = tab_stristr(info->envp, "_=")) >= 0)
	{
		if (!(tmp = ft_realloc(info->envp[i], ft_strlen(path) + 2)))
			ft_exit(info, cmd);
		ft_strcpy(tmp + 2, path);
		info->envp[i] = tmp;
	}
	else
	{
		if (!(tmp = ft_strjoin("_=", path)))
			ft_exit(info, cmd);
		if (!(temp = tab_add_free(info->envp, tmp)))
			ft_exit(info, NULL);
		info->envp = temp;
	}
}

/*
** Searches the directories specified in the PATH variable for matching entries
** of the given command and launches it whether or not a path was found.
*/

int			binexe(t_info *info, t_cmd *cmd, char **bin, char *value)
{
	char	*path;
	int		ret;
	int		i;

	if (!(ft_strcmp(cmd->argv[0], "W")))
		cmd->argv[0][0] = 'w';
	info->ret = NOT_FOUND;
	if (!(value = get_value(info, "PATH=")))
		return (launch(info, cmd, cmd->argv[0], cmd->argv));
	if (!(bin = ft_split(value, ':')))
		ft_exit(info, cmd);
	i = 0;
	path = check_dir(bin[i] + 5, cmd->argv[0]);
	while (!path && bin[i])
		path = check_dir(bin[i++], cmd->argv[0]);
	set__(info, cmd, path);
	if (path)
		ret = launch(info, cmd, path, cmd->argv);
	else
		ret = launch(info, cmd, cmd->argv[0], cmd->argv);
	if (path)
		free(path);
	tab_free(bin);
	return (ret);
}
