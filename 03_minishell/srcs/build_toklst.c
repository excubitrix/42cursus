/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_toklst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:07:21 by floogman          #+#    #+#             */
/*   Updated: 2021/03/24 11:10:06 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks whether two matching quotes are right next to each other.
*/

static void	check_quotes(t_info *info, char **cmd, int quote, int *j)
{
	if (!(*j) && (*((*cmd) + 1) == ' ' || *((*cmd) + 1) == '|'
		|| *((*cmd) + 1) == ';') && ((quote == 1 && **cmd == '\'')
		|| (quote == 2 && **cmd == '\"')))
	{
		info->curtok->data[(*j)++] = ' ';
		next_tok(info, cmd, j);
	}
}

/*
** Seperates the given string into tokens, the result is a linked
** list of type t_tok. The pointer to the list is in the info struct.
*/

void		get_toks(t_info *info, char **cmd)
{
	int		quote;
	int		j;

	j = 0;
	quote = 0;
	while (1)
	{
		if (!quote)
		{
			if (!(check_cases(info, cmd, &quote, &j)))
				if (check_more_cases(info, cmd, &j) < 0)
					ft_exit(info, NULL);
		}
		else
		{
			check_quotes(info, cmd, quote, &j);
			copy_data(info->curtok, cmd, &quote, &j);
		}
		if (**cmd == '\0')
		{
			(j > 0) && (info->curtok->data[j] = **cmd);
			break ;
		}
		(*cmd)++;
	}
}

/*
** Entry point for the creation of the token list.
*/

void		build_toklst(t_info *info, char *cmd)
{
	if (!(info->toklst = malloc(sizeof(t_tok))))
		ft_exit(info, NULL);
	info->curtok = info->toklst;
	if (!(info->curtok = init_tok(info->curtok, info->size)))
		ft_exit(info, NULL);
	get_toks(info, &cmd);
}
