/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 08:39:45 by floogman          #+#    #+#             */
/*   Updated: 2021/05/08 07:55:12 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sb(t_info *info, int **stack, int *size)
{
	int		swap;

	(!info->checker) && info->steps++;
	(!info->checker) && ft_putendl_fd("sb", 1);
	if (size[B] < 2)
		return ;
	swap = stack[B][0];
	stack[B][0] = stack[B][1];
	stack[B][1] = swap;
}

void	pb(t_info *info, int **stack, int *size)
{
	int		tmp;

	(!info->checker) && info->steps++;
	(!info->checker) && ft_putendl_fd("pb", 1);
	if (!size[A])
		return ;
	tmp = pop(stack[A], size[A] - 1);
	push(stack[B], size[B], tmp);
	size[B] += 1;
	size[A] -= 1;
}

void	rb(t_info *info, int **stack, int *size)
{
	int		tmp;

	(!info->checker) && info->steps++;
	(!info->checker) && ft_putendl_fd("rb", 1);
	if (size[B] < 2)
		return ;
	tmp = pop(stack[B], size[B] - 1);
	stack[B][size[B] - 1] = tmp;
}

void	rrb(t_info *info, int **stack, int *size)
{
	(!info->checker) && info->steps++;
	(!info->checker) && ft_putendl_fd("rrb", 1);
	if (size[B] > 1)
		push(stack[B], size[B] - 1, stack[B][size[B] - 1]);
}
