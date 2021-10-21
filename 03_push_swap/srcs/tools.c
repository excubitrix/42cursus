/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 13:42:16 by floogman          #+#    #+#             */
/*   Updated: 2021/04/23 11:13:50 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	get_min_max(int *stack, int size, int *min, int *max)
{
	int		i;

	if (min)
		*min = stack[0];
	if (max)
		*max = stack[0];
	i = -1;
	while (++i < size)
	{
		if (min)
			*min = ft_min(stack[i], *min);
		if (max)
			*max = ft_max(stack[i], *max);
	}
}

void	get_nth_min(int *stack, int size, int n, int *ret)
{
	int		min;
	int		max;
	int		i;
	int		j;

	j = -1;
	get_min_max(stack, size, &min, &max);
	while (++j < n)
	{
		*ret = max;
		i = -1;
		while (++i < size)
			if (stack[i] < *ret && stack[i] > min)
				*ret = stack[i];
		min = *ret;
	}
}

int	calc_chunk(t_info *info, int chunk_size)
{
	int		limit;

	if (info->size[A] >= chunk_size * 3)
		limit = chunk_size * 2;
	else if (info->size[A] >= chunk_size * 2)
		limit = chunk_size;
	else
		limit = info->size[A] - chunk_size;
	get_nth_min(info->stack[A], info->size[A], limit, &info->min);
	if (limit > chunk_size)
		get_nth_min(info->stack[A], info->size[A], chunk_size, &info->mid);
	info->rotate_b = 0;
	return (limit);
}

int	get_num(t_info *info, char *num)
{
	long	result;
	char	sign;
	int		i;

	i = 0;
	if (!num)
		return (0);
	result = 0;
	sign = '+';
	while (ft_isspace(num[i]))
		i++;
	if (num[i] == '-' || num[i] == '+')
		sign = num[i++];
	while (ft_isdigit(num[i]))
		result = result * 10 + (num[i++] - 48);
	if ((num[i] && !ft_isdigit(num[i]) && !ft_isspace(num[i]))
		|| (i > 0 && !ft_isdigit(num[i - 1]) && !ft_isspace(num[i - 1])))
		free_all(info, "Invalid characters found");
	if (sign == '-')
		result = -result;
	if (result > INT_MAX || result < INT_MIN)
		free_all(info, "One or more numbers are out of range");
	return (result);
}

int	is_sorted(t_info *info)
{
	int		i;

	i = -1;
	while (++i < info->size[A] - 1)
		if (info->stack[A][i] > info->stack[A][i + 1])
			return (0);
	(info->checker && info->flag_c) && ft_putstr(GREEN);
	(info->checker) && ft_putstr_endl("OK");
	(info->checker && info->flag_c) && ft_putstr(RESET);
	return (1);
}
