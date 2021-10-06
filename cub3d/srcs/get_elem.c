/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 10:31:53 by floogman          #+#    #+#             */
/*   Updated: 2021/01/23 21:18:04 by floogman         ###   ########.fr       */
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

void	get_color(t_data *s, char *line, int *var)
{
	int		red;
	int		green;
	int		blue;

	if (*var)
		ft_abort(s, 2, __FILE__, __LINE__);
	get_component(s, line, &red, 0);
	get_component(s, line, &green, 0);
	s->col = get_nbr(line, s->col, &blue);
	while (line[s->col])
		if (line[s->col] && line[s->col++] != ' ')
			ft_abort(s, 14, __FILE__, __LINE__);
	if (red < 0 || red > 255 || green < 0 || green > 255
		|| blue < 0 || blue > 255)
		ft_abort(s, 12, __FILE__, __LINE__);
	*var = create_trgb(0, red, green, blue);
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
	int			r;
	int			y;
	int			x;

	if (get_next_line(fd, &line) == -1)
	{
		close(fd);
		ft_abort(s, 0, __FILE__, __LINE__);
	}
	x = 0;
	y = i * s->map.w;
	while ((r = gnl_strchr(line + x, '2')) >= 0 && (x += r) && nbr < s->snbr)
		init_spr(s, nbr++, ++x, i);
	ft_stricat(s->map.ptr, line, y);
	ft_strfill(s->map.ptr, y + ft_strlen(line), y + s->map.w);
	free(line);
}

void	store_map(t_data *s, char *file, int start)
{
	int		fd;
	int		i;

	i = 1;
	s->map.w += 2;
	s->map.size = s->map.w * s->map.h;
	if (!(s->map.ptr = malloc(s->map.size + 1)))
		ft_abort(s, 0, __FILE__, __LINE__);
	if ((fd = open(file, O_RDONLY)) < 0)
		ft_abort(s, 0, __FILE__, __LINE__);
	skip_lines(s, s->line, fd, start);
	ft_strfill(s->map.ptr, 0, s->map.w);
	while (i < s->map.h)
		store_line(s, fd, s->line, i++);
	close(fd);
	s->line = NULL;
	if (!s->map.ptr[skip_space(s->map.ptr)])
		ft_abort(s, 5, __FILE__, __LINE__);
	if (s->map.plr)
		s->map.ptr[(int)s->pos.y * s->map.w + (int)s->pos.x] = '0';
}
