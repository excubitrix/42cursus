/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 14:02:42 by floogman          #+#    #+#             */
/*   Updated: 2021/03/26 18:54:14 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Adapted ft_atoi() function that returns the correct
** exit code.
*/

static int	ft_atoec(const char *nptr)
{
	uintmax_t	result;
	char		sign;

	sign = '+';
	result = 0;
	if (*nptr == '-' || *nptr == '+')
	{
		sign = *nptr;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		result = result * 10 + (*nptr - 48);
		nptr++;
	}
	if ((result - 1 > LONG_MAX && sign == '-')
		|| (result > LONG_MAX && sign != '-'))
		return (-1);
	if (sign == '-')
		result = -result;
	return (result % 256);
}

/*
** Puts en error message to the screen.
*/

static int	put_error(char *s, int ret)
{
	ft_putstr_fd("minishell: exit: ", STDERR);
	ft_putendl_fd(s, STDERR);
	return (ret);
}

/*
** Our build-in exit function. It takes one numeric argument and
** does not exit if piped.
*/

int			ft_exit(t_info *info, t_cmd *cmd)
{
	int		ret;
	int		pipe;

	pipe = 0;
	if (info->pipe_out > 0)
		pipe = 1;
	if (!cmd || (cmd && (ft_strcmp(cmd->argv[0], "exit") ||
		(!ft_strcmp(cmd->argv[0], "exit") && cmd->argc < 2))))
		ret = info->ret;
	else
	{
		if (cmd->argc > 2)
			ret = put_error("too many arguments", FAILURE);
		else if (((cmd->argv[1][0] == '-' || cmd->argv[1][0] == '+')
			&& str_is(cmd->argv[1] + 1, &ft_isdigit))
			|| str_is(cmd->argv[1], &ft_isdigit))
			ret = ft_atoec(cmd->argv[1]);
		else
			ret = put_error("numeric argument required", -1);
	}
	if (pipe)
		return (ret);
	free_all(info, cmd, -1);
	exit(ret);
	return (ret);
}
