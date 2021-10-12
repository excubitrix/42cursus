/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_stristr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 07:47:23 by floogman          #+#    #+#             */
/*   Updated: 2021/02/25 08:59:25 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		tab_stristr(char **haystack, char *needle)
{
	int		i;

	if (!needle)
		return (-1);
	i = 0;
	while (haystack[i])
	{
		if (!(ft_strncmp(haystack[i], needle, ft_strlen(needle))))
			return (i);
		i++;
	}
	return (-1);
}
