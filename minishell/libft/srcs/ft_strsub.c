/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 12:38:35 by floogman          #+#    #+#             */
/*   Updated: 2021/03/23 12:44:13 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char *str, char *sub, int index, int skip)
{
	int		str_len;
	int		sub_len;

	str_len = ft_strlen(str);
	sub_len = ft_strlen(sub);
	if (!(str = ft_realloc(str, str_len + sub_len)))
		return (NULL);
	ft_memmove(&str[index + sub_len], &str[index + skip], str_len - index);
	ft_memcpy(&str[index], sub, sub_len);
	return (str);
}
