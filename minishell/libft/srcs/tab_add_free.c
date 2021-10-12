/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_add_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 09:31:18 by floogman          #+#    #+#             */
/*   Updated: 2021/03/26 09:58:10 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**tab_add_free(char **tab, char *add)
{
	char	**new;
	int		len;

	if (!add)
		return (tab);
	len = tab_size(tab);
	if (!(new = tab_realloc(tab, len + 2)))
		return (NULL);
	if (!(new[len] = ft_strdup(add)))
		tab_free(new);
	free(add);
	return (new);
}
