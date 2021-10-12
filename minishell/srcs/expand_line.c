/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:28:13 by floogman          #+#    #+#             */
/*   Updated: 2021/03/24 11:09:48 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Handles environment variable expansion.
*/

char		*envar_expansion(t_info *info, char *line, int *i)
{
	char	*value;
	char	*key;
	char	*tmp;
	int		len;

	if ((len = get_key(line, *i, &key)) < 0)
		ft_exit(info, NULL);
	value = get_value(info, key);
	free(key);
	if (!(tmp = ft_strsub(line, value, *i, len)))
		ft_exit(info, NULL);
	*i += ft_strlen(value) - 1;
	return (tmp);
}

/*
** Handles exit status expansion.
*/

char		*last_exstat_expansion(t_info *info, char *line, int *i, char next)
{
	char	*value;
	char	*tmp;

	value = NULL;
	if (next == '?')
		if (!(value = ft_itoa(info->ret)))
			ft_exit(info, NULL);
	if (!(tmp = ft_strsub(line, value, *i, 2)))
		ft_exit(info, NULL);
	*i += ft_strlen(value) - 1;
	if (value)
		free(value);
	return (tmp);
}

/*
** Handles tilde expansion.
*/

char		*tilde_expansion(t_info *info, char *line, int *i)
{
	char			*tmp;
	char			*sub;
	int				len;

	len = 0;
	while (!is_sep(line[*i + len]))
		len++;
	if ((is_sep(line[*i + 1]) || line[*i + 1] == '/'))
	{
		if (!(tmp = ft_strsub(line, info->home, *i, 1)))
			ft_exit(info, NULL);
		len = ft_strlen(info->home);
	}
	else
	{
		if (!(sub = check_users(info, &line[*i + 1], len - 1)))
			return (line);
		if (!(tmp = ft_strsub(line, sub, *i, len)))
			ft_exit(info, NULL);
		len = ft_strlen(sub);
		free(sub);
	}
	*i += len - 1;
	return (tmp);
}

/*
** Checks for quotes.
*/

static void	check_quotes(char *line, int i, int *quote)
{
	if (line[i] == '\'')
		*quote = 1;
	if (*quote == 2 && line[i] == '\"')
		*quote = 0;
	if (line[i] == '\"')
		*quote = 2;
}

/*
** Entry point for expansion.
*/

char		*expand_line(t_info *info, char *line, int i, int quote)
{
	while (line[i])
	{
		if (quote != 1)
		{
			check_quotes(line, i, &quote);
			if (line[i] == '$' && ft_isalpha(line[i + 1]))
				line = envar_expansion(info, line, &i);
			else if (line[i] == '$' && (line[i + 1] == '?'
				|| ft_isdigit(line[i + 1])))
				line = last_exstat_expansion(info, line, &i, line[i + 1]);
			else if (line[i] == '~' && (!i || is_sep(line[i - 1])))
				line = tilde_expansion(info, line, &i);
			else if (line[i] == '$' && !quote && ft_isquote(line[i + 1]))
				ft_memmove(&line[i], &line[i + 1], ft_strlen(line) - i);
			if (line[i] == '\\')
				i++;
		}
		else if (line[i] == '\'')
			quote = 0;
		if (i >= 0 && (!line[i] || (!quote && line[i] == ';')))
			break ;
		i++;
	}
	return (line);
}
