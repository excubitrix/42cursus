/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:40:07 by floogman          #+#    #+#             */
/*   Updated: 2021/05/08 07:57:35 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	init_stacks(t_info *info, int **stack, int *size, char **nbrs)
{
	int		num;
	int		j;
	int		i;

	size[A] = info->total;
	stack[A] = malloc(sizeof(int) * info->total);
	stack[B] = malloc(sizeof(int) * info->total);
	if (!stack[A] || !stack[B])
		free_all(info, "Malloc failure");
	i = -1;
	while (nbrs[++i])
	{
		j = -1;
		num = get_num(info, nbrs[i]);
		while (++j < i)
			if (num == stack[A][j])
				free_all(info, "Duplicate integer found");
		stack[A][i] = num;
		stack[B][i] = 0;
	}
	return (0);
}

void	init_op_ptrs(t_info *info)
{
	info->op_str[0] = "sa";
	info->op_str[1] = "sb";
	info->op_str[2] = "ss";
	info->op_str[3] = "pa";
	info->op_str[4] = "pb";
	info->op_str[5] = "ra";
	info->op_str[6] = "rb";
	info->op_str[7] = "rr";
	info->op_str[8] = "rra";
	info->op_str[9] = "rrb";
	info->op_str[10] = "rrr";
	info->op_ptr[0] = &sa;
	info->op_ptr[1] = &sb;
	info->op_ptr[2] = &ss;
	info->op_ptr[3] = &pa;
	info->op_ptr[4] = &pb;
	info->op_ptr[5] = &ra;
	info->op_ptr[6] = &rb;
	info->op_ptr[7] = &rr;
	info->op_ptr[8] = &rra;
	info->op_ptr[9] = &rrb;
	info->op_ptr[10] = &rrr;
}

static void	init_size(t_info *info)
{
	info->size[A] = 0;
	info->size[B] = 0;
	info->size_cpy[A] = 0;
	info->size_cpy[B] = 0;
}

void	init_info(t_info *info, int argc, char **argv, int checker)
{
	int		i;

	info->steps = 0;
	init_size(info);
	info->stack[A] = NULL;
	info->stack[B] = NULL;
	info->stack_cpy[A] = NULL;
	info->stack_cpy[B] = NULL;
	init_op_ptrs(info);
	info->checker = checker;
	info->flag_c = 0;
	info->flag_g = 0;
	info->flag_p = 0;
	info->flag_s = 0;
	info->flag_v = 0;
	i = 1;
	while (argv[i] && argv[i][0] == '-' && is_flag(info, argv[i], 0))
		i++;
	if (argc - i < 2)
		free_all(info, "Insufficient number of arguments");
	info->total = argc - i;
	init_stacks(info, info->stack, info->size, argv + i);
	(info->checker && info->flag_p) && init_stacks(info, info->stack_cpy,
		info->size_cpy, argv + i);
}
