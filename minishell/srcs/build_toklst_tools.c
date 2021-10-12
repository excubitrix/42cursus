/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_toklst_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 08:50:10 by floogman          #+#    #+#             */
/*   Updated: 2021/03/24 09:47:51 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Quoted characters are copied. Copy_data() also checks for the
** matching quote and handles escape characters contained withhin
** double quotes.
*/

void	copy_data(t_tok *tok, char **cmd, int *quote, int *j)
{
	static int	escaped;

	if (*quote == 2 && **cmd == '\\' && (*((*cmd) + 1) == '\\'
		|| *((*cmd) + 1) == '$'))
		tok->data[(*j)++] = *(++(*cmd));
	else if (escaped && (escaped %= 2) && *quote == 2 && **cmd == '\\')
	{
		tok->data[(*j)++] = *(++(*cmd));
		escaped++;
	}
	else
	{
		escaped = 0;
		if ((*quote == 1 && **cmd == '\'') || (*quote == 2 && **cmd == '\"'))
			*quote = 0;
		else if ((*quote == 2 && **cmd == '\'')
			|| (*quote == 1 && **cmd == '\"'))
			tok->data[(*j)++] = **cmd;
		else
			tok->data[(*j)++] = **cmd;
	}
}

/*
** Sets all variables for a non-word token and starts the next token.
*/

void	type_tok(t_info *info, char **cmd)
{
	int		a;

	a = 0;
	if (**cmd == *((*cmd) + 1))
		a = 1;
	info->curtok->data[0] = **cmd;
	info->curtok->data[a] = **cmd;
	info->curtok->data[1 + a] = '\0';
	info->curtok->type = **cmd + a;
	if (!(info->curtok->next = malloc(sizeof(t_tok))))
		ft_exit(info, NULL);
	info->curtok = info->curtok->next;
	if (!(info->curtok = init_tok(info->curtok, info->size)))
		ft_exit(info, NULL);
	if (a)
		(*cmd)++;
}

/*
** Sets all variables for a type -1 (word) token and starts the next
** token.
*/

void	next_tok(t_info *info, char **cmd, int *j)
{
	int		a;

	a = 0;
	if (**cmd == *((*cmd) + 1))
		a = 1;
	info->curtok->data[*j] = '\0';
	if (info->curtok->digit && str_is(info->curtok->data, &ft_isdigit)
		&& (**cmd == '<' || **cmd == '>'))
		info->curtok->type = **cmd + a;
	else if (**cmd != ' ')
		info->curtok->type = -1;
	if (!(info->curtok->next = malloc(sizeof(t_tok))))
		ft_exit(info, NULL);
	info->curtok = info->curtok->next;
	if (!(info->curtok = init_tok(info->curtok, info->size)))
		ft_exit(info, NULL);
	*j = 0;
}

/*
** If a space or a special character is encountered and data is not
** empty, the current token is stopped and a new one is started. If
** it was a special character, a non-word token is also created.
*/

int		check_more_cases(t_info *info, char **cmd, int *j)
{
	if (**cmd == ' ')
	{
		if (*j > 0)
			next_tok(info, cmd, j);
	}
	else if (**cmd != 0)
	{
		if (*j > 0)
			next_tok(info, cmd, j);
		type_tok(info, cmd);
	}
	return (SUCCESS);
}

/*
** Checks for escape characters, quotes and non-special characters
** and handles them accordingly. If neither was found, more cases
** are checked.
*/

int		check_cases(t_info *info, char **cmd, int *quote, int *j)
{
	int		c;

	c = get_type(**cmd);
	if (c == '\\')
	{
		info->curtok->data[(*j)++] = *(++(*cmd));
		info->curtok->type = -1;
		info->curtok->digit = 0;
		return (1);
	}
	else if (c < 0 || c == '\'' || c == '\"')
	{
		if (c == '\'')
			*quote = 1;
		if (c == '\"')
			*quote = 2;
		if (c < 0)
			info->curtok->data[(*j)++] = **cmd;
		info->curtok->type = -1;
		return (1);
	}
	return (0);
}
