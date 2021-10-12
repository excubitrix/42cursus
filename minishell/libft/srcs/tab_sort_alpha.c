/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_sort_alpha.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 11:03:11 by floogman          #+#    #+#             */
/*   Updated: 2020/09/27 11:35:37 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	tab_sort_alpha(char **tab, char c)
{
	int		i;
	int		len;
	char	*ptr;
	char	*tmp;

	i = 0;
	while (tab[i] && tab[i + 1])
	{
		ptr = ft_strchr(tab[i], c);
		len = ptr - tab[i];
		ptr = ft_strchr(tab[i + 1], c);
		len = ft_min(len, ptr - tab[i + 1]);
		if (0 < (ft_strncmp(tab[i], tab[i + 1], len)))
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}
