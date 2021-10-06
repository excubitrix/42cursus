/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:15:11 by floogman          #+#    #+#             */
/*   Updated: 2021/01/21 15:05:52 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		skip_space(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
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

void	save_pos(t_data *s, int i, char dir)
{
	if (s->map.plr)
	{
		s->ln = s->map.h - 1;
		s->col = i;
		ft_abort(s, 15, __FILE__, __LINE__);
	}
	set_pos(s, dir, i + 0.5, s->map.h - 0.5);
	s->map.plr = 1;
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
