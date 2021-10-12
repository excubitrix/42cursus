/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 19:13:50 by floogman          #+#    #+#             */
/*   Updated: 2021/03/24 18:47:04 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks that the greater-than and less-than signs are followed
** by non-special characters.
*/

int		check_redir(char *cmd, int *first, int *i, int c)
{
	int		j;

	*first = 0;
	if (cmd[*i + 1] == c)
		(*i)++;
	if (c == '<' && cmd[*i + 1] == c)
		(*i)++;
	j = *i + 1;
	while (cmd[j] == ' ')
		j++;
	if (is_special(cmd[j]) > 0)
		return (set_and_return(i, j, FAILURE));
	if (cmd[j] == '\0')
	{
		cmd[*i] = '\n';
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
** Checks that the special characters are followed by non-special
** characters.
*/

int		check_special(char *cmd, int *first, int *i, int c)
{
	int		j;

	if (*first)
		return (FAILURE);
	j = *i + 1;
	if (c == ';' || c == '&')
	{
		if (cmd[j] == ';')
			return (set_and_return(i, j, FAILURE));
		if (!*first && !(cmd[*i] == '&' && cmd[*i + 1] == '&'))
			return (set_and_return(first, 1, SUCCESS));
	}
	if ((c == '&' && cmd[j] == '&') || (c == '|' && cmd[j] == '|'))
		j++;
	while (cmd[j] == ' ')
		j++;
	if (is_special(cmd[j]) > 0)
		return (set_and_return(i, j, FAILURE));
	if (cmd[j] == '\0')
		return (FAILURE);
	return (SUCCESS);
}

/*
** Entry point for the checking of the syntax.
*/

int		check_syntax(char *cmd, int first, int quote, int i)
{
	char	c;

	while (1)
	{
		c = get_type(cmd[i]);
		if (!quote)
		{
			if (check_general(&first, &quote, &i, c))
				;
			else if ((c == '<' || c == '>')
				&& (check_redir(cmd, &first, &i, c)))
				return (i);
			else if (c != '\0' && (check_special(cmd, &first, &i, c)))
				return (i);
		}
		else if ((quote == 1 && c == '\'')
			|| (quote == 2 && c == '\"'))
			quote = 0;
		else if (quote == 2 && c == '\\')
			i++;
		if (c == '\0' || c == '#')
			break ;
		i++;
	}
	return (i);
}
