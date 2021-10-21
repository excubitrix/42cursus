/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:37:16 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:00:06 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "bmp.h"

void	write_pixels(t_data *s, int fd)
{
	int				x;
	int				y;
	unsigned char	clr[3];

	y = s->win.h - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < s->win.w)
		{
			clr[2] = (unsigned char)get_rgb(get_pixel(s->img, x, y), 'r');
			clr[1] = (unsigned char)get_rgb(get_pixel(s->img, x, y), 'g');
			clr[0] = (unsigned char)get_rgb(get_pixel(s->img, x, y), 'b');
			write(fd, clr, 3);
			x++;
		}
		y--;
	}
}

void	ft_itoc(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

void	write_header(t_data *s, int fd, int size)
{
	int				i;
	int				tmp;
	unsigned char	header[54];

	i = 0;
	while (i < 54)
		header[i++] = (unsigned char)(0);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	ft_itoc(header + 2, size);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	tmp = s->win.w;
	ft_itoc(header + 18, tmp);
	tmp = s->win.h;
	ft_itoc(header + 22, tmp);
	header[27] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	write(fd, header, 54);
}

void	save_img_to_bmp(t_data *s)
{
	int		fd;
	int		size;
	int		padding;

	init_game(s, 1);
	cast_floor(s, 0);
	cast_walls(s, 0);
	cast_sprites(s, 0);
	draw_hud(s);
	padding = (4 - (s->win.w * 3) % 4) % 4;
	size = 54 + (3 * ((s->win.w + padding) * s->win.h));
	if ((fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) < 0)
		ft_abort(s, 0, __FILE__, __LINE__);
	write_header(s, fd, size);
	write_pixels(s, fd);
	close(fd);
	ft_exit(s);
}
