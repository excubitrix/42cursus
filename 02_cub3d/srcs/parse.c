/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:13:32 by floogman          #+#    #+#             */
/*   Updated: 2021/01/23 08:27:06 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_elem(t_data *s, char *line)
{
	int		type;

	s->elem++;
	type = gnl_strchr("NSWE", line[s->col]);
	if (line[s->col] == 'R')
		get_res(s, &s->win, line);
	else if (line[s->col] == 'F' && !ft_isalpha(line[s->col + 1]))
		get_color(s, line + s->col + 1, &s->floor);
	else if (line[s->col] == 'C' && !ft_isalpha(line[s->col + 1]))
		get_color(s, line + s->col + 1, &s->ceiling);
	else if (((type == 0 || type == 1) && line[s->col + 1] == 'O')
		|| (type == 2 && line[s->col + 1] == 'E')
		|| (type == 3 && line[s->col + 1] == 'A'))
		get_texture(s, line, type, s->col + 2);
	else if (line[s->col] == 'S')
		get_texture(s, line, 4, s->col + 1);
	else
		ft_abort(s, 1, __FILE__, __LINE__);
}

void	parse_map(t_data *s, char *line)
{
	t_map	*map;
	char	*dir;

	map = &s->map;
	if (map->parsing != -1)
		map->parsing = 1;
	else
		ft_abort(s, 14, __FILE__, __LINE__);
	while (line[s->col])
	{
		if (line[s->col] == '2')
			s->snbr++;
		else if (line[s->col] && (dir = ft_strchr("NSWE", line[s->col])))
			save_pos(s, s->col + 1, *dir);
		s->col++;
	}
	map->w = map->w > s->col ? map->w : s->col;
	map->h++;
}

void	parse_line(t_data *s, char *line, int *start, int i)
{
	s->ln++;
	if (line[i] && s->elem < 8 && ft_strchr("RNSWEFC", line[i]))
	{
		if (s->map.parsing)
			ft_abort(s, 7, __FILE__, __LINE__);
		else
			parse_elem(s, line);
	}
	else if (line[i] && !ft_strchr("012 ", line[i]))
		ft_abort(s, 14, __FILE__, __LINE__);
	if (!line[i] && s->map.parsing)
		s->map.parsing = -1;
	if (s->map.parsing == 1 || line[i] == '1')
		parse_map(s, line);
	else if (!s->map.parsing)
		(*start)++;
	free(s->line);
}

void	parse_scene(t_data *s, char *file, int start)
{
	int		fd;
	int		ret;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_abort(s, 0, __FILE__, __LINE__);
	while ((ret = get_next_line(fd, &s->line)) > 0)
	{
		s->col = skip_space(s->line);
		parse_line(s, s->line, &start, s->col);
	}
	if (ret == -1)
	{
		close(fd);
		ft_abort(s, 0, __FILE__, __LINE__);
	}
	if (s->line)
	{
		s->col = skip_space(s->line);
		parse_line(s, s->line, &start, s->col);
	}
	close(fd);
	s->line = NULL;
	if (!(s->spr = malloc(sizeof(t_vec *) * s->snbr)))
		ft_abort(s, 0, __FILE__, __LINE__);
	store_map(s, file, start);
}
