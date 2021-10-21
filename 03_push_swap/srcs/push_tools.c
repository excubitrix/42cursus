/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 09:08:55 by floogman          #+#    #+#             */
/*   Updated: 2021/05/08 07:56:26 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	pop(int *array, int size)
{
	int		top;
	int		i;

	top = array[0];
	i = -1;
	while (++i < size)
		array[i] = array[i + 1];
	array[i] = 0;
	return (top);
}

void	push(int *array, int size, int push)
{
	int		i;

	i = size - 1;
	while (i >= 0)
	{
		array[i + 1] = array[i];
		i--;
	}
	array[0] = push;
}

static void	reset_indexes(t_info *info)
{
	info->i_max = 0;
	info->i_2nd_max = 0;
	info->i_min = 0;
}

void	get_indexes(t_info *info, int *stack, int size)
{
	int		i;

	i = -1;
	reset_indexes(info);
	while (++i < size)
	{
		if (stack[i] < stack[info->i_min])
			info->i_min = i;
		if (stack[i] > stack[info->i_max])
		{
			info->i_2nd_max = info->i_max;
			info->i_max = i;
		}
		else if (stack[i] > stack[info->i_2nd_max])
			info->i_2nd_max = i;
		else if (info->i_2nd_max == info->i_max)
			info->i_2nd_max = i;
	}
}

void	index_to_top(t_info *info, int stack, int size, int index)
{
	if (index <= size / 2)
	{
		while (index != 0)
		{
			if (stack == A)
				ra(info, info->stack, info->size);
			else
				rb(info, info->stack, info->size);
			index--;
		}
	}
	else
	{
		while (index != 0)
		{
			if (stack == A)
				rra(info, info->stack, info->size);
			else
				rrb(info, info->stack, info->size);
			if (index == size - 1)
				index = 0;
			else
				index++;
		}
	}
}
