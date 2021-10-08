/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:28:25 by floogman          #+#    #+#             */
/*   Updated: 2021/05/08 07:51:13 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_abort(t_info *info, char *tofree, char *msg)
{
	if (tofree)
		free(tofree);
	free_all(info, msg);
}

static int	get_padding(t_info *info, int min, int max)
{
	int		a;
	int		b;

	if (info->flag_g && (min < 0 && max > 0))
		return (abs(min) + abs(max));
	else if (info->flag_g)
		return (ft_max(abs(min), abs(max)));
	a = 1;
	(min < 0) && a++;
	while (min / 10)
	{
		min /= 10;
		a++;
	}
	b = 1;
	(max < 0) && b++;
	while (max / 10)
	{
		max /= 10;
		b++;
	}
	a = ft_max(a, b);
	if (a % 2)
		a++;
	return (a);
}

static int	get_line(t_info *info, char **line, char *tmp)
{
	char	buf[1];
	int		bytes;
	int		ret;

	if (!tmp)
		free_all(info, "Malloc failure");
	bytes = 0;
	while (bytes < BUFFER)
	{
		ret = read(0, &buf, 1);
		if (ret != 1 || buf[0] == '\n')
			break ;
		tmp[bytes++] = buf[0];
	}
	if (ret < 0)
		ft_abort(info, tmp, "Read failure");
	if (!ret && !bytes)
	{
		free(tmp);
		tmp = NULL;
	}
	*line = tmp;
	return (bytes + ret);
}

static void	parse_ops(t_info *info, char *line, int pad, int i)
{
	if (!get_line(info, &line, ft_calloc(sizeof(char), BUFFER)))
		return ;
	while (line && ft_strcmp(line, ""))
	{
		i = -1;
		while (++i < 11)
		{
			if (!ft_strcmp(line, info->op_str[i]))
			{
				(*info->op_ptr[i])(info, info->stack, info->size);
				info->steps++;
				(info->flag_p) && print_stacks(info, info->stack, line, pad);
				(*info->op_ptr[i])(info, info->stack_cpy, info->size_cpy);
				break ;
			}
		}
		if (i == 11)
			ft_abort(info, line, "Invalid instruction");
		free(line);
		if (!get_line(info, &line, ft_calloc(sizeof(char), BUFFER)))
			break ;
	}
	if (line && !ft_strcmp(line, ""))
		free(line);
}

int	main(int argc, char **argv)
{
	t_info	info;
	char	*line;
	int		pad;

	line = NULL;
	if (argc == 1)
		return (1);
	init_info(&info, argc, argv, 1);
	get_min_max(info.stack[A], info.size[A], &info.min, &info.max);
	pad = ft_max(6, get_padding(&info, info.min, info.max));
	(info.flag_p) && print_stacks(&info, info.stack, "", pad);
	parse_ops(&info, line, pad, 0);
	if (info.size[A] != info.total || !is_sorted(&info))
	{
		(info.flag_c) && ft_putstr(RED);
		ft_putstr_endl("KO");
		(info.flag_c) && ft_putstr(RESET);
	}
	(info.flag_s) && print_steps(&info);
	free_all(&info, NULL);
	return (0);
}
