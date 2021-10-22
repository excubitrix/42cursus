/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 19:38:42 by floogman          #+#    #+#             */
/*   Updated: 2021/10/22 10:34:08 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../minilibx_opengl_20191021/mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h> // perror
# include <errno.h>
# include <math.h>

# define MAX_SCREEN_WIDTH 2560
# define MAX_SCREEN_HEIGHT 1400
# define MIN_SCREEN_WIDTH 400
# define MIN_SCREEN_HEIGHT 240

# define RED "\033[0;91m"
# define BLACK "\033[0;90m"
# define RE "\033[0m"

# define ERRNUM	18

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124

typedef struct	s_vec
{
	double		x;
	double		y;
}				t_vec;

typedef struct	s_xy
{
	int			x;
	int			y;
}				t_xy;

typedef struct	s_win
{
	void		*ptr;
	int			w;
	int			h;
}				t_win;

typedef struct	s_img
{
	void		*ptr;
	char		*addr;
	char		*path;
	int			w;
	int			h;
	int			bpp;
	int			ll;
	int			endian;
	double		x;
	double		y;
	double		step;
	double		pos;
}				t_img;

typedef struct	s_vars
{
	double		pwd;
	t_vec		spr;
	double		invdet;
	t_vec		transf;
	double		wallx;
	int			screenx;
	int			h;
	int			w;
	t_xy		start;
	t_xy		end;
}				t_vars;

typedef struct	s_map
{
	char		*ptr;
	int			w;
	int			h;
	int			x;
	int			y;
	int			size;
	int			plr;
	int			parsing;
}				t_map;

typedef struct	s_key
{
	int			a;
	int			s;
	int			d;
	int			w;
	int			left;
	int			right;
}				t_key;

typedef struct	s_data
{
	char		*line;
	int			ln;
	int			col;
	void		*mlx;
	t_win		win;
	t_img		img;
	t_vars		v;
	t_img		tex[5];
	int			ceiling;
	int			floor;
	t_map		map;
	t_vec		**spr;
	int			snbr;
	int			*sorder;
	double		*sdst;
	int			elem;
	double		*zbuffer;
	t_vec		pos;
	t_vec		dir;
	t_vec		pln;
	t_vec		ray;
	t_vec		dlt;
	t_vec		step;
	t_vec		side;
	t_key		key;
	char		**errmsg;
}				t_data;

int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
int				create_trgb(int t, int r, int g, int b);
int				add_shadow(double shd, int clr);

int				get_pixel(t_img img, int x, int y);
void			put_pixel(t_data *s, int x, int y, int clr);
void			draw_ver_line(t_data *s, t_xy xy, int end, int clr);
void			draw_bg(t_data *s, int x);

void			free_spr(t_data *s);
void			free_tex(t_data *s);
int				ft_exit(t_data *s);
void			ft_abort(t_data *s, int msg, char *file, int line);
void			init_errmsg(t_data *s);

void			get_res(t_data *s, t_win *win, char *line);
void			get_color(t_data *s, char *line, int *var);
void			get_texture(t_data *s, char *line, int texnbr, int i);
void			store_line(t_data *s, int fd, char *line, int i);
void			store_map(t_data *s, char *file, int start);

int				ft_kpress(int keycode, t_data *s);
int				ft_krelease(int keycode, t_data *s);
int				render_frame(t_data *s);

int				set_pos(t_data *s, char dir, double x, double y);
int				set_dir(t_data *s, char c);
int				set_pln(t_data *s, char c);

void			init_game(t_data *s, int bmp);
void			init_spr(t_data *s, int i, int x, int y);
void			init_tex(t_data *s);
void			init_map(t_data *s);
void			init_s(t_data *s);

int				check_input(t_data *s, int argc, char **argv);
int				check_adjacent_tiles(t_xy **queue, int x, int y);
int				iter_flood_fill(t_data *s, char *map, int ret, int error);
void			check_map(t_data *s);
void			is_valid(t_data *s);

void			ft_move(t_data *data, double varx, double vary);
void			ft_rotate(t_data *data, double var);
int				movement(t_data *data);

int				skip_space(char *str);
void			skip_lines(t_data *s, char *line, int fd, int n);
void			save_pos(t_data *s, int i, char dir);
int				get_nbr(char *line, int i, int *ptr);
void			get_component(t_data *s, char *line, int *ptr, int res);

void			parse_elem(t_data *s, char *line);
void			parse_map(t_data *s, char *line);
void			parse_line(t_data *s, char *line, int *start, int i);
void			parse_scene(t_data *s, char *file, int start);

t_xy			**queue_calloc(int size);
t_xy			*new_point(int x, int y);
int				add_queue(t_xy **queue, int x, int y);
void			free_queue(t_xy **xy);

int				ft_sort(int *order, double *tosort, int nbr);
int				sort_sprites(t_data *s);
int				calc_sprite(t_data *s, t_vars *v);
int				draw_sprite(t_data *s, t_vars v, int x, int y);
int				cast_sprites(t_data *s);

void			store_ln_col(t_data *s, int ln, int col);
void			ft_swap(int *tab, int i);
void			ft_strfill(char *str, int i, int n);
void			ft_stricat(char *dest, char *src, int i);
void			load_textures(t_data *s);

void			calc_step(t_data *s);
int				find_wall(t_data *s, int *side, int *face);
void			calc_height(t_data *s, int side, int *y, int nbr);
void			draw_wall(t_data *s, int x, int side, int face);
void			cast_walls(t_data *s);

#endif
