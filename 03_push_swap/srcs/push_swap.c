/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 13:25:24 by floogman          #+#    #+#             */
/*   Updated: 2021/04/23 11:12:49 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	move_chunk(t_info *info, int *stack, int size, int limit)
{
	int		count;

	count = 0;
	while (count < limit)
	{
		if (info->stack[A][0] <= info->min)
		{
			if (limit > size && info->size[B] > 1 && stack[0] <= info->mid)
			{
				rb(info, info->stack, info->size);
				info->rotate_b = 0;
			}
			pb(info, info->stack, info->size);
			if (limit > size && stack[0] <= info->mid)
				info->rotate_b = 1;
			count++;
		}
		else if (info->rotate_b)
		{
			rr(info, info->stack, info->size);
			info->rotate_b = 0;
		}
		else
			ra(info, info->stack, info->size);
	}
}

void	sort_three(t_info *info, int **stack)
{
	get_indexes(info, stack[A], info->size[A]);
	if ((info->i_min == 0 && info->i_max == 1)
		|| (info->i_2nd_max != 2 && stack[A][0] > stack[A][1]))
	{
		if (info->size[B] > 1 && stack[B][0] < stack[B][1])
			ss(info, stack, info->size);
		else
			sa(info, stack, info->size);
	}
	if (!is_sorted(info) && info->i_2nd_max == 2)
		ra(info, stack, info->size);
	else if (!is_sorted(info))
		rra(info, stack, info->size);
}

void	move_b_to_a(t_info *info, int first_dst, int second_dst)
{
	get_indexes(info, info->stack[B], info->size[B]);
	first_dst = info->i_max;
	second_dst = info->i_2nd_max;
	if (info->i_max > info->size[B] / 2)
		first_dst = info->size[B] - first_dst;
	if (info->i_2nd_max > info->size[B] / 2)
		second_dst = info->size[B] - second_dst;
	if (first_dst <= second_dst)
		index_to_top(info, B, info->size[B], info->i_max);
	else
		index_to_top(info, B, info->size[B], info->i_2nd_max);
	pa(info, info->stack, info->size);
	get_indexes(info, info->stack[B], info->size[B]);
	index_to_top(info, B, info->size[B], info->i_max);
	pa(info, info->stack, info->size);
	if (first_dst > second_dst)
	{
		if (info->size[B] > 1 && info->stack[B][0] < info->stack[B][1])
			ss(info, info->stack, info->size);
		else
			sa(info, info->stack, info->size);
	}
}

void	push_swap(t_info *info, int chunk_size)
{
	while (chunk_size && info->size[A] > chunk_size && !is_sorted(info))
		move_chunk(info, info->stack[B], chunk_size,
			calc_chunk(info, chunk_size));
	while ((info->size[A] > 3 || (info->size[A] < 3 && info->size[A] > 1))
		&& !is_sorted(info))
	{
		get_indexes(info, info->stack[A], info->size[A]);
		index_to_top(info, A, info->size[A], info->i_min);
		if (!is_sorted(info))
			pb(info, info->stack, info->size);
	}
	if (info->size[A] == 3 && !is_sorted(info))
		sort_three(info, info->stack);
	while (info->size[B] > 1)
		move_b_to_a(info, 0, 0);
	if (info->size[B])
		pa(info, info->stack, info->size);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc == 1)
		return (1);
	init_info(&info, argc, argv, 0);
	if (!is_sorted(&info))
	{
		if (info.total <= 5)
			push_swap(&info, 0);
		if (info.total <= 25)
			push_swap(&info, 5);
		if (info.total <= 50)
			push_swap(&info, 15);
		if (info.total <= 250)
			push_swap(&info, info.total / 10);
		if (info.total > 250)
			push_swap(&info, info.total / 15);
	}
	(info.flag_s) && print_steps(&info);
	free_all(&info, NULL);
	return (0);
}
