/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:11:09 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:07:10 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_ln_col(t_data *s, int ln, int col)
{
	s->ln = ln + 1;
	s->col = col + 1;
}

void	ft_swap(int *tab, int i)
{
	int swap;

	swap = tab[i];
	tab[i] = tab[i + 1];
	tab[i + 1] = swap;
}

void	ft_strfill(char *str, int i, int n)
{
	while (str[i])
		i++;
	while (i < n)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
}

void	ft_stricat(char *dest, char *src, int i)
{
	int j;

	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
}

int		get_snbr(t_data *s, int x, int y)
{
	int		i;

	i = 0;
	while (i < s->snbr)
	{
		if ((int)s->spr[i]->x == x && (int)s->spr[i]->y == y)
			return (i);
		i++;
	}
	return (-1);
}
