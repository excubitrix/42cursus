/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 09:31:18 by floogman          #+#    #+#             */
/*   Updated: 2021/03/18 11:30:34 by floogman         ###   ########.fr       */
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
		prev = i > 0 ? str[i - 1] : '\0';
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
	if (!(word = (char *)malloc(sizeof(char) * (i + 1))))
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

char		**ft_split(char const *s, char c)
{
	int		i;
	char	**tab;

	if (!s || !(tab = malloc(sizeof(char *) * (count_words(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			if (!(tab[i] = malloc_word(s, c)))
			{
				tab_free(tab);
				return (NULL);
			}
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	tab[i] = NULL;
	return (tab);
}
