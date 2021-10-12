/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_toklst_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:07:21 by floogman          #+#    #+#             */
/*   Updated: 2021/03/24 08:58:00 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

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
** Reattaches the severed end of the linked list in case of a malloc
** error in wildcard_expansion().
*/

static void	ft_abort(t_info *info, t_tok *saved)
{
	info->curtok->next = saved;
	ft_exit(info, NULL);
}

/*
** Inserts tokens into the list for all matches found by the glob()
** function called in build_toklst().
*/

int			wildcard_expansion(t_info *info, glob_t globbuf)
{
	t_tok	*saved;
	size_t	i;

	saved = info->curtok->next;
	free(info->curtok->data);
	if (!(info->curtok->data = malloc(ft_strlen(globbuf.gl_pathv[0]) + 1)))
		ft_abort(info, saved);
	if (!(ft_strcpy(info->curtok->data, globbuf.gl_pathv[0])))
		ft_abort(info, saved);
	i = 1;
	while (i < globbuf.gl_pathc)
	{
		if (!(info->curtok->next = malloc(sizeof(t_tok))))
			ft_abort(info, saved);
		if (!(info->curtok = init_tok(info->curtok->next,
			ft_strlen(globbuf.gl_pathv[i]))))
			ft_abort(info, saved);
		info->curtok->type = -1;
		if (!(ft_strcpy(info->curtok->data, globbuf.gl_pathv[i])))
			ft_abort(info, saved);
		i++;
	}
	info->curtok->next = saved;
	return (SUCCESS);
}

/*
** Entry point for the creation of the token list. Once the list is
** created, it iterates through the tokens and invokes the glob()
** function on each of the tokens with type -1 (word), which expands,
** if present, the wildcard pattern into a list of pathnames matching
** the pattern.
*/

void		build_toklst(t_info *info, char *cmd)
{
	glob_t	globbuf;

	if (!(info->toklst = malloc(sizeof(t_tok))))
		ft_exit(info, NULL);
	info->curtok = info->toklst;
	if (!(info->curtok = init_tok(info->curtok, info->size)))
		ft_exit(info, NULL);
	get_toks(info, &cmd);
	info->curtok = info->toklst;
	while (info->curtok != NULL)
	{
		if (info->curtok->type == -1)
		{
			glob(info->curtok->data, GLOB_TILDE, NULL, &globbuf);
			if (globbuf.gl_pathc > 0)
				wildcard_expansion(info, globbuf);
			globfree(&globbuf);
		}
		info->curtok = info->curtok->next;
	}
}
