/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 09:53:01 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:44:32 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t newsize)
{
	char	*newptr;
	size_t	size;

	if (!ptr)
		return (malloc(newsize * sizeof(char *)));
	size = sizeof(ptr);
	if (newsize <= size)
		return (ptr);
	newptr = malloc(newsize * sizeof(char *));
	ft_memcpy(newptr, ptr, size);
	free(ptr);
	return (newptr);
}
