/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 12:54:35 by floogman          #+#    #+#             */
/*   Updated: 2021/01/21 13:40:33 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_xy	**queue_calloc(int size)
{
	t_xy	**queue;
	int		i;

	i = 0;
	if (!(queue = malloc(sizeof(t_xy *) * (size + 1))))
		return (NULL);
	while (i <= size)
	{
		queue[i] = NULL;
		i++;
	}
	return (queue);
}

t_xy	*new_point(int x, int y)
{
	t_xy	*new;

	if (!(new = malloc(sizeof(t_xy))))
		return (NULL);
	new->x = x;
	new->y = y;
	return (new);
}

int		add_queue(t_xy **queue, int x, int y)
{
	t_xy	*new;
	int		i;

	i = 0;
	if (!(new = new_point(x, y)))
		return (0);
	if (!queue[i])
		queue[i] = new;
	else
	{
		while (queue[i])
		{
			if (new->x == queue[i]->x && new->y == queue[i]->y)
			{
				free(new);
				return (1);
			}
			i++;
		}
		queue[i] = new;
	}
	return (1);
}

void	free_queue(t_xy **xy)
{
	int		i;

	i = 0;
	if (!xy)
		return ;
	while (xy[i])
	{
		free(xy[i]);
		i++;
	}
	free(xy);
}
