/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 09:31:18 by floogman          #+#    #+#             */
/*   Updated: 2020/01/23 12:16:53 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	str_len;

	if (s)
	{
		str_len = ft_strlen(s);
		if (start > str_len)
			return (ft_strdup(""));
		if ((str_len - start) < len)
			len = str_len - start;
		if (!(substr = malloc(len + 1)))
			return (NULL);
		substr[0] = '\0';
		ft_memcpy(substr, s + start, len);
		substr[len] = '\0';
		return (substr);
	}
	return (NULL);
}
