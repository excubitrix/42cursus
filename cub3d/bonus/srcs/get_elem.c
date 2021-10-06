/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 10:31:53 by floogman          #+#    #+#             */
/*   Updated: 2021/01/23 21:18:21 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_res(t_data *s, t_win *win, char *line)
{
	if (win->w && win->h)
		ft_abort(s, 2, __FILE__, __LINE__);
	s->col++;
	get_component(s, line, &win->w, 1);
	s->col = get_nbr(line, s->col, &win->h);
	while (line[s->col])
	{
		if (line[s->col] && line[s->col] != ' ')
			ft_abort(s, 14, __FILE__, __LINE__);
		s->col++;
	}
	if (win->w > MAX_SCREEN_WIDTH || win->h > MAX_SCREEN_HEIGHT)
	{
		ft_printf(BLACK"The declared resolution is greater "
			"than the display resolution.\nResizing window...\n"RE);
		win->w = win->w > MAX_SCREEN_WIDTH ? MAX_SCREEN_WIDTH : win->w;
		win->h = win->h > MAX_SCREEN_HEIGHT ? MAX_SCREEN_HEIGHT : win->h;
	}
	if (win->w < MIN_SCREEN_WIDTH || win->h < MIN_SCREEN_HEIGHT)
	{
		ft_printf(BLACK"The declared resolution is smaller "
			"than the set minimum.\nResizing window...\n"RE);
		win->w = win->w < MIN_SCREEN_WIDTH ? MIN_SCREEN_WIDTH : win->w;
		win->h = win->h < MIN_SCREEN_HEIGHT ? MIN_SCREEN_HEIGHT : win->h;
	}
}

void	get_texture(t_data *s, char *line, int texnbr, int i)
{
	char	*path;
	int		fd;

	while (isspace(line[i]))
		i++;
	s->col = i;
	if (line[s->col] == '\0')
		ft_abort(s, 3, __FILE__, __LINE__);
	while (!isspace(line[s->col]) && line[s->col])
		s->col++;
	if (!(path = ft_strndup(line + i, s->col - i)))
		ft_abort(s, 0, __FILE__, __LINE__);
	if (!s->tex[texnbr].path)
		s->tex[texnbr].path = path;
	else
		ft_abort(s, 2, __FILE__, __LINE__);
	while (line[s->col])
	{
		if (line[s->col] && line[s->col] != ' ')
			ft_abort(s, 14, __FILE__, __LINE__);
		s->col++;
	}
	if ((fd = open(path, O_RDONLY)) < 0)
		ft_abort(s, 0, __FILE__, __LINE__);
	close(fd);
}

void	store_line(t_data *s, int fd, char *line, int i)
{
	static int	nbr;
	int			tex;
	int			y;
	t_vec		t;

	if (get_next_line(fd, &line) == -1)
	{
		close(fd);
		ft_abort(s, 0, __FILE__, __LINE__);
	}
	t.x = 0;
	t.y = i;
	y = i * s->map.w;
	while (line[(int)t.x] && nbr < s->snbr)
	{
		if ((tex = gnl_strchr("______2345IH", line[(int)t.x])) > 5)
			init_spr(s, nbr++, tex, t);
		t.x++;
	}
	ft_stricat(s->map.ptr, line, y);
	ft_strfill(s->map.ptr, y + ft_strlen(line), y + s->map.w);
	if (line)
		free(line);
}

void	store_map(t_data *s, char *file, int start)
{
	int		fd;
	int		i;

	i = 0;
	s->map.size = s->map.w * s->map.h;
	if (!(s->map.ptr = malloc(s->map.size + 1)))
		ft_abort(s, 0, __FILE__, __LINE__);
	if ((fd = open(file, O_RDONLY)) < 0)
		ft_abort(s, 0, __FILE__, __LINE__);
	s->map.ptr[0] = '\0';
	skip_lines(s, s->line, fd, start);
	while (i < s->map.h)
		store_line(s, fd, s->line, i++);
	close(fd);
	s->line = NULL;
	if (!s->map.ptr[0])
		ft_abort(s, 5, __FILE__, __LINE__);
	if (s->map.plr)
		s->map.ptr[(int)s->plr.pos.y * s->map.w + (int)s->plr.pos.x] = '0';
}
