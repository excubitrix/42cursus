/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 09:31:18 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 10:16:03 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char sep)
{
	int		i;
	int		count;
	char	prev;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (i > 0)
			prev = str[i - 1];
		else
			prev = 0;
		if (prev == sep && str[i] != sep)
			count++;
		i++;
	}
	return (count);
}

static char	*malloc_word(char const *str, char sep)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	word = malloc((i + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != sep)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	*split_free(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
		free(tab[i++]);
	free(tab);
	tab = NULL;
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**tab;

	if (s)
		tab = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			tab[i] = malloc_word(s, c);
			if (!tab[i++])
				return (split_free(tab));
			while (*s && *s != c)
				s++;
		}
	}
	tab[i] = NULL;
	return (tab);
}
