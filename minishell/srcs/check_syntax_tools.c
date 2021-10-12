/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:55:51 by floogman          #+#    #+#             */
/*   Updated: 2021/03/26 09:13:22 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Helps reduce lines in the other functions.
*/

int		set_and_return(int *ptr, int var, int ret)
{
	*ptr = var;
	return (ret);
}

/*
** Checks whether the int passed matches any of the following
** characters: null, semicolon, pipe, greater-than, less-than,
** ampersand.
*/

int		is_special(int c)
{
	if (c == '\0' || c == ';' || c == '|' || c == '>' || c == '<'
		|| c == '&')
		return (c);
	return (-1);
}

/*
** Checks for escape characters, quotes and non-special characters
** and handles them accordingly. If neither was found, more checks
** are made.
*/

int		check_general(int *first, int *quote, int *i, int c)
{
	if (c == '\\' || c < 0 || c == ' ')
	{
		if (c != ' ')
			*first = 0;
		if (c == '\\')
			(*i)++;
		return (1);
	}
	if (ft_isquote(c))
	{
		*quote = 1;
		if (c == '\"')
			(*quote)++;
		*first = 0;
		return (1);
	}
	return (0);
}
