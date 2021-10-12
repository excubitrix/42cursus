/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_strstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 09:31:18 by floogman          #+#    #+#             */
/*   Updated: 2021/02/26 10:30:17 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*tab_strstr(char **haystack, char *needle)
{
	int		i;

	if (!needle)
		return (NULL);
	i = 0;
	while (haystack[i])
	{
		if ((ft_strnstr(haystack[i], needle, ft_strlen(haystack[i]))))
			return (haystack[i]);
		i++;
	}
	return (NULL);
}
