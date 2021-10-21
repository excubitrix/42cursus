/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_delone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 09:31:18 by floogman          #+#    #+#             */
/*   Updated: 2020/10/09 09:47:40 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	tab_delone(char **tab, char *one)
{
	char	*tmp;
	int		i;

	if (!tab || !one)
		return ;
	i = 0;
	while (tab[i])
	{
		if (!(ft_strncmp(tab[i], one, ft_strlen(one))))
			break ;
		i++;
	}
	if (!tab[i])
		return ;
	while (tab[i] && tab[i + 1])
	{
		tmp = tab[i];
		tab[i] = tab[i + 1];
		tab[i + 1] = tmp;
		i++;
	}
	free(tab[i]);
	tab[i] = NULL;
}
