/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 14:00:41 by floogman          #+#    #+#             */
/*   Updated: 2021/03/24 13:52:51 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prints the string pointed to by argv[i]. It also performs
** checks to determine whether or not a space needs to be appended.
*/

static void	print_arg(char **argv, int i, int fd, int first)
{
	static int	word;

	if (first)
	{
		if (ft_strcmp(argv[i], " "))
		{
			ft_putstr_fd(argv[i], fd);
			word = 1;
		}
		else if (argv[i + 1])
			ft_putstr_fd(argv[i], fd);
		return ;
	}
	if (word && ft_strcmp(argv[i], " "))
		ft_putchar_fd(' ', fd);
	if (ft_strcmp(argv[i], " "))
		word = 1;
	ft_putstr_fd(argv[i], fd);
}

/*
** Checks whether the argument given matches the '-n' option.
*/

static int	is_n(char *arg)
{
	int		i;

	i = 1;
	if (arg[0] == '-' && arg[i] == 'n')
	{
		while (arg[i] == 'n')
			i++;
		if (!arg[i])
			return (1);
	}
	return (0);
}

/*
** Print_args() iterates through char **argv and passes each
** string through print_arg() to be printed. If the '-n' option
** is not active, a newline is put at the end.
*/

static void	print_args(char **argv, int n, int fd)
{
	int		i;

	i = 1;
	if (*argv == NULL)
		return ;
	while (argv[i] && is_n(argv[i]))
		i++;
	if (argv[i])
	{
		print_arg(argv, i, fd, 1);
		i++;
		while (argv[i])
		{
			print_arg(argv, i, fd, 0);
			i++;
		}
	}
	if (!n)
		ft_putchar_fd('\n', fd);
}

/*
** The entry point for our build-in echo command.
*/

int			ft_echo(t_info *info, t_cmd *cmd)
{
	(void)info;
	if (cmd->argc > 1 && is_n(cmd->argv[1]))
		print_args(cmd->argv, 1, STDOUT);
	else
		print_args(cmd->argv, 0, STDOUT);
	return (SUCCESS);
}
