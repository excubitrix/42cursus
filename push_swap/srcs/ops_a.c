/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 08:38:43 by floogman          #+#    #+#             */
/*   Updated: 2021/05/08 07:54:23 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_info *info, int **stack, int *size)
{
	int		swap;

	(!info->checker) && info->steps++;
	(!info->checker) && ft_putendl_fd("sa", 1);
	if (size[A] < 2)
		return ;
	swap = stack[A][0];
	stack[A][0] = stack[A][1];
	stack[A][1] = swap;
}

void	pa(t_info *info, int **stack, int *size)
{
	int		tmp;

	(!info->checker) && info->steps++;
	(!info->checker) && ft_putendl_fd("pa", 1);
	if (!size[B])
		return ;
	tmp = pop(stack[B], size[B] - 1);
	push(stack[A], size[A], tmp);
	size[A] += 1;
	size[B] -= 1;
}

void	ra(t_info *info, int **stack, int *size)
{
	int		tmp;

	(!info->checker) && info->steps++;
	(!info->checker) && ft_putendl_fd("ra", 1);
	if (size[A] < 2)
		return ;
	tmp = pop(stack[A], size[A] - 1);
	stack[A][size[A] - 1] = tmp;
}

void	rra(t_info *info, int **stack, int *size)
{
	(!info->checker) && info->steps++;
	(!info->checker) && ft_putendl_fd("rra", 1);
	if (size[A] > 1)
		push(stack[A], size[A] - 1, stack[A][size[A] - 1]);
}
