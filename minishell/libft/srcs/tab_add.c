/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:30:11 by floogman          #+#    #+#             */
/*   Updated: 2021/03/26 11:17:51 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**tab_add(char **tab, char *add)
{
	char	**new;
	int		len;

	if (!add)
		return (tab);
	len = tab_size(tab);
	if (!(new = tab_realloc(tab, len + 1)))
		return (NULL);
	if (!(new[len] = ft_strdup(add)))
		tab_free(new);
	return (new);
}
