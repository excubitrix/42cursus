/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:29:50 by floogman          #+#    #+#             */
/*   Updated: 2021/03/18 11:29:51 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**tab_dup(char **tab)
{
	int		i;
	char	**cpy;

	if (!tab || !(cpy = malloc(sizeof(char *) * (tab_size(tab) + 1))))
		return (NULL);
	i = 0;
	while (tab[i])
	{
		if (!(cpy[i] = ft_strdup(tab[i])))
		{
			tab_free(cpy);
			return (NULL);
		}
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
