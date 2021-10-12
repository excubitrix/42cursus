/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_realloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 09:53:01 by floogman          #+#    #+#             */
/*   Updated: 2021/03/18 10:53:24 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**tab_realloc(char **ptr, size_t newsize)
{
	char	**newptr;
	size_t	size;
	size_t	i;

	if (!(newptr = malloc(sizeof(char *) * (newsize + 1))))
		return (NULL);
	if (ptr)
	{
		size = tab_size(ptr);
		if (newsize <= size)
			return (ptr);
		i = 0;
		while (ptr[i])
		{
			newptr[i] = ft_strdup(ptr[i]);
			i++;
		}
		while (i <= newsize)
		{
			newptr[i] = NULL;
			i++;
		}
		tab_free(ptr);
	}
	return (newptr);
}
