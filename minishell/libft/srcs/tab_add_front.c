/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_add_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 09:53:01 by floogman          #+#    #+#             */
/*   Updated: 2021/03/22 21:17:11 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_abort(char **tab)
{
	tab_free(tab);
	return (NULL);
}

char		**tab_add_front(char **tab, char *add)
{
	char	**new;
	size_t	size;
	size_t	i;
	int		j;

	size = tab_size(tab);
	if (!(new = malloc(sizeof(char *) * (size + 2))))
		return (NULL);
	i = 0;
	if (add)
		if (!(new[i++] = ft_strdup(add)))
			ft_abort(new);
	j = 0;
	while (tab[j])
		if (!(new[i++] = ft_strdup(tab[j++])))
			ft_abort(new);
	new[i] = NULL;
	tab_free(tab);
	return (new);
}
