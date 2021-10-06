/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 09:53:01 by floogman          #+#    #+#             */
/*   Updated: 2020/01/26 12:28:58 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t newsize)
{
	char	*newptr;
	size_t	size;

	if (ptr == NULL)
		return (malloc(newsize * sizeof(char *)));
	size = sizeof(ptr);
	if (newsize <= size)
		return (ptr);
	newptr = malloc(newsize * sizeof(char *));
	ft_memcpy(newptr, ptr, size);
	free(ptr);
	return (newptr);
}
