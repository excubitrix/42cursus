/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:01:51 by floogman          #+#    #+#             */
/*   Updated: 2021/09/28 13:37:47 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	gnl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == c)
				return (i);
			i++;
		}
		if (s[i] == c)
			return (i);
	}
	return (-1);
}

char	*gnl_strndup(char *s1, int n)
{
	char	*s2;

	if (!s1)
		return (gnl_strndup("", 2));
	else if (n < 0)
		return (gnl_strndup(s1, gnl_strlen(s1)));
	s2 = malloc((n + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	s2[n] = '\0';
	while (n--)
		s2[n] = s1[n];
	return (s2);
}

char	*gnl_strsubdup(char *s, int start, int end)
{
	int		new_len;
	char	*new_s;

	new_len = end - start;
	new_s = malloc((new_len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	new_s[new_len] = '\0';
	while (new_len-- && end--)
		new_s[new_len] = s[end];
	free(s);
	return (new_s);
}

char	*gnl_strjoin(char *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*output;

	i = 0;
	j = 0;
	len = gnl_strlen(s1) + gnl_strlen(s2);
	output = malloc((len + 1) * sizeof(char));
	if (!output)
		return (NULL);
	while (len-- && s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	while (len-- && s2[j])
	{
		output[i + j] = s2[j];
		j++;
	}
	output[i + j] = s2[j];
	output[i + j + 1] = '\0';
	free(s1);
	return (output);
}
