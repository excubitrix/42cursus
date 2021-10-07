/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 08:14:05 by floogman          #+#    #+#             */
/*   Updated: 2021/10/04 11:01:42 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*result;

	result = malloc((n + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[n] = '\0';
	return (ft_memcpy(result, s, n));
}
