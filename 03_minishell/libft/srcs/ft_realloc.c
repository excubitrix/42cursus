/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 09:53:01 by floogman          #+#    #+#             */
/*   Updated: 2021/02/28 07:44:58 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t newsize)
{
	char	*newptr;
	size_t	size;

	if (ptr == NULL)
		return (malloc((newsize + 1) * sizeof(char)));
	size = ft_strlen(ptr);
	if (newsize <= size)
		return (ptr);
	newptr = ft_calloc(newsize + 1, sizeof(char));
	ft_memcpy(newptr, ptr, size);
	free(ptr);
	return (newptr);
}
