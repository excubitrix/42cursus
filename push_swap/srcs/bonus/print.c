/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:27:39 by floogman          #+#    #+#             */
/*   Updated: 2021/04/23 10:45:47 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_divider(int len, int div)
{
	int		i;

	i = -1;
	while (i++ < len)
	{
		if (i == div)
			printf(" ");
		printf("-");
	}
	printf(NEWLINE);
}

static int	set_color(t_info *info, int **stack, int l, int i)
{
	if (i == 0 && info->size_cpy[l] < info->size[l])
		printf(BLUE);
	else if (info->size_cpy[l] < info->size[l]
		|| (i == info->size[l] && stack[l][i] == info->stack_cpy[l][0])
		|| (i > 0 && (stack[l][i] == info->stack_cpy[l][i - 1]
		|| stack[l][i] == info->stack_cpy[l][0])))
		printf(RED);
	else if (info->size_cpy[l] > info->size[l]
		|| (i == 0 && info->size[l] > 1
			&& stack[l][i] == info->stack_cpy[l][info->size_cpy[l] - 1])
		|| (i >= 0 && stack[l][i] == info->stack_cpy[l][i + 1]))
		printf(GREEN);
	return (0);
}

static void	print_bar(t_info *info, int l, int i, int *j)
{
	(info->flag_c) && set_color(info, info->stack, l, i);
	if (info->stack[l][i] < 0)
		while ((*j)++ < info->stack[l][i])
			printf(" ");
	if (info->stack[l][i] < 0)
		while ((*j)++ <= 0)
			printf(".");
	else if (info->min < 0)
		while ((*j)++ < 0)
			printf(" ");
	printf("%5d ", info->stack[l][i]);
	if (info->stack[l][i] >= 0)
		while ((*j)++ <= info->stack[l][i])
			printf(".");
	printf(RESET);
}

void	print_graph(t_info *info, int pad, int i)
{
	int		j;

	printf("%*c%*c"NEWLINE, abs(info->min) + 4, 'A', pad + 8, 'B');
	print_divider((pad * 2) + 13, pad + 7);
	while (++i < info->total)
	{
		j = info->min;
		if (i < info->size[A])
			print_bar(info, A, i, &j);
		else
			j -= 4;
		if (i < info->size[B])
		{
			while (++j < info->max + 5)
				printf(" ");
			j = info->min;
			print_bar(info, B, i, &j);
		}
		printf(NEWLINE);
	}
	printf(NEWLINE);
	(!info->flag_v && info->flag_c) && system("sleep 0.05");
	(!info->flag_v) && system("sleep 0.05");
}

void	print_def(t_info *info, int **stack, int pad, int i)
{
	printf("%*c%*c%*c"NEWLINE, (pad / 2) + 2, 'A', pad / 2, '|',
		pad / 2, 'B');
	print_divider(pad * 2, 0);
	while (++i < info->total)
	{
		if (i < info->size[A])
		{
			(info->flag_c) && set_color(info, stack, A, i);
			printf("%*d"RESET"|", pad + 1, stack[A][i]);
		}
		else
			printf("%*c|", pad + 1, ' ');
		if (i < info->size[B])
		{
			(info->flag_c) && set_color(info, stack, B, i);
			printf("%*d"RESET NEWLINE, pad, stack[B][i]);
		}
		else
			printf("%*c"NEWLINE, pad, ' ');
	}
	printf(NEWLINE);
	(!info->flag_v && info->flag_c) && system("sleep 0.05");
	(!info->flag_v) && system("sleep 0.05");
}
