/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:41:03 by floogman          #+#    #+#             */
/*   Updated: 2021/03/24 19:07:58 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks for quotes and escape characters.
*/

static void	check_quotes(char *ptr, int *i, int *quote)
{
	if (!*quote && ptr[*i] == '\'')
		*quote = 1;
	if (!*quote && ptr[*i] == '\"')
		*quote = 2;
	else if (*quote == 2 && ptr[*i] == '\"')
		*quote = 0;
	if (ptr[*i] == '\\')
		(*i)++;
}

/*
** Checks whether we are dealing with a logical AND (&&) or a logical
** OR (||) and, if so, sets the corresponding variables accordingly.
*/

int			set_and_or(t_info *info, char *ptr, int *i)
{
	if (ptr[*i] == '&' && ptr[*i + 1] == '&')
	{
		info->and = 1;
		(*i)++;
		return (1);
	}
	if (ptr[*i] == '|' && ptr[*i + 1] == '|')
	{
		info->or = 1;
		(*i)++;
		return (1);
	}
	return (0);
}

/*
** Creates a sub-string containing the first command and removes its contents
** from the "mother-string".
*/

char		*get_cmd(t_info *info, char *ptr, char *tmp, char *cmd)
{
	int		quote;
	int		i;

	i = 0;
	quote = 0;
	while (ptr[i])
	{
		if (!quote && (ptr[i] == ';' || ptr[i] == '#' || ptr[i] == '&'
			|| (ptr[i] == '|' && ptr[i + 1] == '|')))
			break ;
		if (quote != 1)
			check_quotes(ptr, &i, &quote);
		else if (ptr[i] == '\'')
			quote = 0;
		i++;
	}
	set_and_or(info, ptr, &i);
	if (ptr[i] && ptr[i] != '#')
		i++;
	cmd = ft_strndup(ptr, i);
	tmp = ft_strdup(ptr + i);
	free(info->line);
	info->line = tmp;
	info->cmd = expand_line(info, cmd, 0, 0);
	return (info->cmd);
}
