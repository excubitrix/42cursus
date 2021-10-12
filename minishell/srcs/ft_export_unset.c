/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 13:13:56 by floogman          #+#    #+#             */
/*   Updated: 2021/03/26 14:33:34 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Puts an error message to the screen.
*/

static int	put_error(char *cmd, char *s)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(": `", STDERR);
	ft_putstr_fd(s, STDERR);
	ft_putendl_fd("': not a valid identifier", STDERR);
	return (FAILURE);
}

/*
** Puts the expected output when export is called without any arguments. It is
** the equivalent of 'export -p' in bash and therefore not mandatory but here
** anyway.
*/

static void	print_declare(t_info *info, t_cmd *cmd, int *order, int i)
{
	int		sign;
	int		j;

	if (!(order = tab_order_by(info->envp, &str_isgreater)))
		ft_exit(info, cmd);
	while (info->envp[i])
	{
		j = 0;
		sign = 0;
		ft_putstr_fd("declare -x ", STDOUT);
		while (info->envp[order[i]][j])
		{
			if (j > 0 && info->envp[order[i]][j - 1] == '=')
				sign = 1;
			if (sign && info->envp[order[i]][j - 1] == '=')
				write(STDOUT, "\"", 1);
			write(STDOUT, &info->envp[order[i]][j], 1);
			j++;
		}
		if (sign)
			write(STDOUT, "\"", 1);
		write(STDOUT, "\n", 1);
		i++;
	}
	free(order);
}

int			is_valid(char *arg, int *append)
{
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			break ;
		i++;
	}
	if (arg[i] == '+')
	{
		ft_memmove(&arg[i], &arg[i + 1],
			ft_strlen(arg) - i);
		*append = 1;
	}
	if ((!ft_isalpha(arg[0]) && arg[0] != '_')
		|| (arg[i] && arg[i] != '='))
		return (-1);
	return (i);
}

/*
** Our build-in export function. It takes multiple arguments. If an argument is
** valid, the list of environment varibales is changed or expanded accordingly.
*/

int			ft_export(t_info *info, t_cmd *cmd)
{
	int		append;
	int		i;
	int		j;

	if (cmd->argc == 1)
		print_declare(info, cmd, NULL, 0);
	i = 1;
	while (cmd->argv[i])
	{
		append = 0;
		if ((j = is_valid(cmd->argv[i], &append)) < 0)
			return (put_error("export", cmd->argv[i]));
		if ((set_envar(info, cmd->argv[i], &cmd->argv[i][j + 1], append)) < 0)
			ft_exit(info, cmd);
		i++;
	}
	return (SUCCESS);
}

/*
** Out build-in unset function. It takes multiple arguments. If an argument is
** valid, the varibale matching the argument is deleted from the list of
** environment varibales if present.
*/

int			ft_unset(t_info *info, t_cmd *cmd)
{
	char	*ptr;
	char	*one;
	int		i;

	i = 0;
	while (cmd->argv[i])
	{
		ptr = cmd->argv[i];
		while (*ptr && *ptr != ' ')
			ptr++;
		if (*ptr || (!ft_isalpha(cmd->argv[i][0]) && cmd->argv[i][0] != '_'))
			return (put_error("unset", cmd->argv[i]));
		if (!(one = ft_strjoin(cmd->argv[i], "=")))
			ft_exit(info, cmd);
		tab_delone(info->envp, one);
		free(one);
		i++;
	}
	return (SUCCESS);
}
