/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 09:47:31 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:13:18 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_input(t_data *s, int argc, char **argv)
{
	char	*ptr;
	int		bmp;
	int		fd;

	bmp = 0;
	if (argc < 2)
		ft_abort(s, 9, __FILE__, __LINE__);
	if (argc > 3)
		ft_abort(s, 10, __FILE__, __LINE__);
	if (!(ptr = ft_strchr(argv[1], '.')) || ft_strcmp(ptr, ".cub"))
		ft_abort(s, 18, __FILE__, __LINE__);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		ft_abort(s, 0, __FILE__, __LINE__);
	close(fd);
	if (argc == 3 && !ft_strcmp(argv[2], "--save"))
		bmp = 1;
	if (!bmp && argc != 2)
		ft_abort(s, 11, __FILE__, __LINE__);
	return (bmp);
}

/*
**	For an 8-directional wall-check,
**		add the following lines to the if statement below:
**	!(add_queue(queue, x - 1, y - 1)) ||
**	!(add_queue(queue, x + 1, y - 1)) ||
**	!(add_queue(queue, x - 1, y + 1)) ||
**	!(add_queue(queue, x + 1, y + 1)) ||
*/

int		check_adjacent_tiles(t_xy **queue, int x, int y)
{
	if (!(add_queue(queue, x, y - 1)) ||
		!(add_queue(queue, x - 1, y)) ||
		!(add_queue(queue, x + 1, y)) ||
		!(add_queue(queue, x, y + 1)))
		return (0);
	return (1);
}

int		iter_flood_fill(t_data *s, char *map, int ret, int error)
{
	t_xy	**queue;
	int		tile;
	int		i;

	i = -1;
	if (!(queue = queue_calloc(s->map.size)) ||
		!(add_queue(queue, s->pos.x, s->pos.y)))
		error = 1;
	while (!error && ret && queue[++i] && i < s->map.size)
	{
		store_ln_col(s, queue[i]->y, queue[i]->x);
		tile = queue[i]->y * s->map.w + queue[i]->x;
		if (map[tile] == '1' || map[tile] == 'X')
			continue ;
		if (map[tile] != '0' && map[tile] != '2')
			ret = 0;
		map[tile] = 'X';
		if (ret && !(check_adjacent_tiles(queue, queue[i]->x, queue[i]->y)))
			error = 1;
	}
	free_queue(queue);
	free(map);
	if (error)
		ft_abort(s, 0, __FILE__, __LINE__);
	return (ret);
}

void	check_map(t_data *s)
{
	char	*cpy;
	int		i;

	i = 0;
	while (s->map.ptr[i])
	{
		if (!ft_strchr("012 ", s->map.ptr[i]))
		{
			s->ln = i / s->map.w;
			s->col = i % s->map.w;
			ft_abort(s, 16, __FILE__, __LINE__);
		}
		i++;
	}
	if (!(cpy = ft_strdup(s->map.ptr)))
		ft_abort(s, 0, __FILE__, __LINE__);
	if (!iter_flood_fill(s, cpy, 1, 0))
		ft_abort(s, 17, __FILE__, __LINE__);
}

void	is_valid(t_data *s)
{
	if (s->elem < 8)
		ft_abort(s, 8, __FILE__, __LINE__);
	else if (!s->map.plr)
		ft_abort(s, 6, __FILE__, __LINE__);
	else if (s->map.w < 5 || s->map.h < 5)
		ft_abort(s, 4, __FILE__, __LINE__);
	check_map(s);
}
