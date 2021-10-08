/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 13:28:47 by floogman          #+#    #+#             */
/*   Updated: 2021/04/15 15:56:58 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ss(t_info *info, int **stack, int *size)
{
	int		swap;

	(!info->checker) && info->steps++;
	(!info->checker) && ft_putendl_fd("ss", 1);
	if (size[A] > 1)
	{
		swap = stack[A][0];
		stack[A][0] = stack[A][1];
		stack[A][1] = swap;
	}
	if (size[B] > 1)
	{
		swap = stack[B][0];
		stack[B][0] = stack[B][1];
		stack[B][1] = swap;
	}
}

void	rr(t_info *info, int **stack, int *size)
{
	int		tmp;

	(!info->checker) && info->steps++;
	(!info->checker) && ft_putendl_fd("rr", 1);
	if (size[A])
	{
		tmp = pop(stack[A], size[A] - 1);
		stack[A][size[A] - 1] = tmp;
	}
	if (size[B])
	{
		tmp = pop(stack[B], size[B] - 1);
		stack[B][size[B] - 1] = tmp;
	}
}

void	rrr(t_info *info, int **stack, int *size)
{
	(!info->checker) && info->steps++;
	(!info->checker) && ft_putendl_fd("rrr", 1);
	if (size[A])
		push(stack[A], size[A], stack[A][size[A] - 1]);
	if (size[B])
		push(stack[B], size[B], stack[B][size[B] - 1]);
}
