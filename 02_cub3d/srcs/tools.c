/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:11:09 by floogman          #+#    #+#             */
/*   Updated: 2021/01/19 15:20:16 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_ln_col(t_data *s, int ln, int col)
{
	s->ln = ln - 1;
	s->col = col - 1;
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
	dest[i++] = ' ';
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
}

void	load_textures(t_data *s)
{
	int		nbr;

	nbr = 0;
	while (nbr < 5)
	{
		if (!(s->tex[nbr].ptr = mlx_xpm_file_to_image(s->mlx,
			s->tex[nbr].path, &s->tex[nbr].w, &s->tex[nbr].h))
			|| !(s->tex[nbr].addr = mlx_get_data_addr(s->tex[nbr].ptr,
			&s->tex[nbr].bpp, &s->tex[nbr].ll, &s->tex[nbr].endian)))
			ft_abort(s, 0, __FILE__, __LINE__);
		nbr++;
	}
}
