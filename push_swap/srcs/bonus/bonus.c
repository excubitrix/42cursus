/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 12:48:48 by floogman          #+#    #+#             */
/*   Updated: 2021/04/23 10:46:57 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_flag(t_info *info, char *arg, int i)
{
	while (arg[++i])
	{
		if (arg[i] == 'c')
			info->flag_c = 1;
		else if (arg[i] == 'g')
		{
			info->flag_p = 1;
			info->flag_g = 1;
		}
		else if (arg[i] == 'p')
			info->flag_p = 1;
		else if (arg[i] == 's')
			info->flag_s = 1;
		else if (arg[i] == 'v')
		{
			info->flag_p = 1;
			info->flag_v = 1;
		}
		else
			return (0);
	}
	return (1);
}

int	print_steps(t_info *info)
{
	printf("[");
	(info->flag_c) && printf(HONEY);
	printf("%d"RESET"]"NEWLINE, info->steps);
	return (0);
}

static void	do_check(t_info *info, int pad)
{
	if (!info->flag_v && info->total > 60)
		free_all(info, "Non-verbose printing is "
			"only supported for up to 60 numbers");
	if (info->flag_g && (pad > 100 || info->min == INT_MIN))
		free_all(info, "Graph printing is only supported for numbers "
			"between -100 and 100 with a max range of a 100");
	if (!info->flag_g && info->total > 9999999)
		free_all(info, "Table printing is only supported for up to "
			"9999999 numbers");
}

int	print_stacks(t_info *info, int **stack, char *op, int pad)
{
	do_check(info, pad);
	printf(HIDE_CURSOR);
	(!info->flag_v && ft_strcmp(op, "")) && printf(START, info->total + 7);
	if (info->flag_g)
	{
		printf(NEWLINE" %*s:", pad + 6, "action ");
		(info->flag_c) && printf(CYAN);
		printf("%5s"RESET NEWLINE"%*s :%5d"NEWLINE NEWLINE, op, pad + 6,
			"   #   ", info->steps);
		print_graph(info, pad, -1);
	}
	else
	{
		printf(NEWLINE"%*s:", pad + 1, "action ");
		(info->flag_c) && printf(CYAN);
		printf("%5s"RESET NEWLINE"%*s:%5d"NEWLINE NEWLINE, op, pad + 1,
			"   #   ", info->steps);
		print_def(info, stack, pad, -1);
	}
	printf(SHOW_CURSOR);
	return (0);
}
