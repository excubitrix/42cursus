/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ft_atoi_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:40:10 by mfabri            #+#    #+#             */
/*   Updated: 2021/03/12 20:40:12 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_get_n_num(char *s)
{
	int n;

	n = 0;
	while (*s)
	{
		while (*s && !ft_isdigit(*s))
			s++;
		if (ft_isdigit(*s))
		{
			n++;
			while (*s && ft_isdigit(*s))
				s++;
		}
	}
	return (n);
}

int		*ft_atoi_array(char *s)
{
	int n;
	int *array;
	int i;

	n = ft_get_n_num(s);
	if (!(array = malloc(sizeof(int) * (n + 1))))
		return (array);
	i = -1;
	while (*s)
	{
		while (*s && !ft_isdigit(*s))
			s++;
		if (ft_isdigit(*s))
		{
			array[++i] = ft_atoi(s);
			while (*s && ft_isdigit(*s))
				s++;
		}
	}
	array[++i] = -1;
	return (array);
}
