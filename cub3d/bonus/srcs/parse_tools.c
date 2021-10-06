/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:15:11 by floogman          #+#    #+#             */
/*   Updated: 2021/01/21 14:55:04 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	get_tile(t_data *s, int x, int y)
{
	return (s->map.ptr[y * s->map.w + x]);
}

void	set_tile(t_data *s, int x, int y, char c)
{
	s->map.ptr[y * s->map.w + x] = c;
}

void	skip_lines(t_data *s, char *line, int fd, int n)
{
	while (n--)
	{
		if (get_next_line(fd, &line) == -1)
		{
			close(fd);
			ft_abort(s, 0, __FILE__, __LINE__);
		}
		free(line);
	}
}

int		get_nbr(char *line, int i, int *ptr)
{
	if (ft_isdigit(line[i]))
		*ptr = ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	return (i);
}

void	get_component(t_data *s, char *line, int *ptr, int res)
{
	while (line[s->col] == ' ')
		s->col++;
	if (line[s->col] == '\0')
		ft_abort(s, 3, __FILE__, __LINE__);
	if (!ft_isdigit(line[s->col]))
		ft_abort(s, 14, __FILE__, __LINE__);
	s->col = get_nbr(line, s->col, ptr);
	if (line[s->col] == '\0')
		ft_abort(s, 3, __FILE__, __LINE__);
	if (!res && line[s->col++] != ',')
		ft_abort(s, 14, __FILE__, __LINE__);
	while (line[s->col] == ' ')
		s->col++;
	if (line[s->col] == '\0')
		ft_abort(s, 3, __FILE__, __LINE__);
	if (!ft_isdigit(line[s->col]))
		ft_abort(s, 14, __FILE__, __LINE__);
}
