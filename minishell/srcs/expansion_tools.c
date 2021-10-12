/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:11:38 by floogman          #+#    #+#             */
/*   Updated: 2021/03/26 14:30:12 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks whether the given int matches any of the following characters: null,
** semicolon, pipe, space, ampersand, less-than, greater-than.
*/

int		is_sep(int c)
{
	if (c == '\0' || c == ';' || c == '|' || c == ' ' || c == '&'
		|| c == '<' || c == '>')
		return (1);
	return (0);
}

/*
** Creates a string used to search info->envp in get_value().
*/

int		get_key(char *s, int i, char **key)
{
	char	*tmp;
	int		len;

	len = 1;
	while (ft_isalnum(s[i + len]))
		len++;
	if (!(tmp = ft_strndup(s + i + 1, len - 1)))
		return (FAILURE);
	if (!(*key = mini_strjoin(tmp, ft_strdup("="), NULL)))
		return (FAILURE);
	return (len);
}

/*
** Retrieves key's value.
*/

char	*get_value(t_info *info, char *key)
{
	int		j;
	char	*ptr;

	ptr = NULL;
	if (key)
		if ((j = tab_stristr(info->envp, key)) >= 0)
			ptr = info->envp[j] + ft_strlen(key);
	return (ptr);
}

/*
** Used by tilde_expansion().
*/

char	*check_users(t_info *info, char *s, int len)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*sub;

	sub = NULL;
	if (!(dir = opendir("/Users")))
		ft_exit(info, NULL);
	while ((entry = readdir(dir)))
	{
		if (!ft_strncmp(entry->d_name, s, len)
			&& len == (int)ft_strlen(entry->d_name))
		{
			if (!(sub = ft_strjoin("/Users/", entry->d_name)))
				ft_exit(info, NULL);
			break ;
		}
	}
	closedir(dir);
	return (sub);
}
