/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_order_by.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 11:03:11 by floogman          #+#    #+#             */
/*   Updated: 2021/03/18 11:28:23 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap(int *tab, int i)
{
	int		swap;

	swap = tab[i];
	tab[i] = tab[i + 1];
	tab[i + 1] = swap;
}

int			*tab_order_by(char **tab, int (*condition)(char *, char *))
{
	int		*order;
	int		size;
	int		i;
	int		j;

	size = tab_size(tab);
	if (!(order = malloc(sizeof(int *) * size)))
		return (NULL);
	i = 0;
	while (i++ < size)
		order[i] = i;
	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size - 1)
		{
			if (condition(tab[order[i]], tab[order[i + 1]]))
				ft_swap(order, i);
			i++;
		}
		j++;
	}
	return (order);
}
