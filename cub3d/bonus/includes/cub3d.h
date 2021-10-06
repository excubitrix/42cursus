/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 19:38:42 by floogman          #+#    #+#             */
/*   Updated: 2021/01/23 20:04:46 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../minilibx_opengl_20191021/mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>

# define MAX_SCREEN_WIDTH 1920
# define MAX_SCREEN_HEIGHT 1040
# define MIN_SCREEN_WIDTH 400
# define MIN_SCREEN_HEIGHT 240

# define RED "\033[0;91m"
# define BLUE "\033[0;94m"
# define BLACK "\033[0;90m"
# define RE "\033[0m"

# define ERRNUM	18

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_E 14
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_SPACE 49
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_SHIFT 257

# define FLOOR 4
# define CEILING 5
# define SKY 10
# define DOOR 11
# define BAR 21
# define HEALTH 22
# define INVENTORY 23
# define ITEMS 24
# define ZERO 25
# define ONE 26
# define TWO 27
# define THREE 28
# define COUNTER 29
# define COUNTER_BG 30
# define LOOSE 31
# define WIN 32
# define EMPTY 33
# define TEXNUM 34

# define FULL 0.95
# define CRITICAL 0.28
# define DEAD 0.11

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
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
	t_vec		step;
	t_vec		pos;
}				t_img;

typedef struct	s_vars
{
	double		pwd;
	int			side;
	int			face;
	double		wallx;
	t_vec		rayo;
	t_vec		rayi;
	int			p;
	double		rowdst;
	t_vec		step;
	t_vec		spr;
	double		invdet;
	t_vec		transf;
	int			screenx;
	double		h;
	double		w;
	int			ver_move;
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
	t_vec		ctr;
	int			size;
	int			plr;
	int			energy;
	int			parsing;
}				t_map;

typedef struct	s_spr
{
	int			tex;
	int			door;
	int			hit;
	int			trap;
	int			open;
	int			bldy;
	double		x;
	double		y;
	double		t;
	double		tt;
}				t_spr;

typedef struct	s_inv
{
	int			i;
	int			ii;
	int			iii;
	int			iv;
}				t_inv;

typedef struct	s_plr
{
	t_vec		pos;
	t_vec		dir;
	double		hp;
	double		old_hp;
	t_inv		inv;
	int			energy;
}				t_plr;

typedef struct	s_ray
{
	t_vec		dir;
	t_vec		dlt;
	t_vec		step;
	double		pitch;
}				t_ray;

typedef struct	s_key
{
	int			a;
	int			s;
	int			d;
	int			w;
	int			e;
	int			space;
	int			shift;
	int			left;
	int			right;
	int			down;
	int			up;
	int			jump;
}				t_key;

typedef struct	s_data
{
	char		*line;
	int			ln;
	int			col;
	t_vars		v;
	t_vec		time;
	double		last_start_song;
	double		last_start_beat;
	void		*mlx;
	t_win		win;
	t_img		img;
	t_img		tex[34];
	t_spr		**spr;
	int			door[2][5];
	t_map		map;
	int			snbr;
	int			*sorder;
	double		*sdst;
	int			elem;
	double		*zbuffer;
	double		*dbuffer;
	double		scaler;
	t_plr		plr;
	t_ray		ray;
	t_vec		pln;
	t_vec		dst;
	t_key		key;
	int			sound;
	int			game_over;
	char		**errmsg;
}				t_data;

void			take(t_data *s);
void			heal(t_data *s);
int				checkin_inv(t_inv *inv);
void			checkout_inv(t_inv	*inv, int nbr);
void			do_action(t_data *s, t_plr plr, t_vec pln);

void			ft_open_close(t_data *s, double var, int x);
void			ft_pick_up(t_data *s, t_plr *plr, double var, int x);
void			ft_use_item(t_data *s, t_inv *inv, int nbr);

int				get_rgb(int trgb, char c);
int				create_trgb(int t, int r, int g, int b);
int				add_shadow(double shd, int clr);
int				change_opc(double opc, int clr, int current);

void			open_close(t_data *s, int open, double diff, int i);
void			door_animation(t_data *s, double time, int i);
void			automated_close(t_data *s, t_spr *spr, t_plr *plr, int *hit);
void			doors(t_data *s, double time);
void			init_door(t_data *s);

int				get_pixel(t_img img, int x, int y);
int				get_pixel_img(t_data *s, int x, int y);
void			put_pixel(t_data *s, int x, int y, int clr);

void			free_spr(t_data *s);
void			free_tex(t_data *s);
int				ft_exit(t_data *s);
void			ft_abort(t_data *s, int msg, char *file, int line);
void			init_errmsg(t_data *s);

void			calc_sky(t_data *s, double *angle, int x);
int				draw_sky(t_data *s, int y, int x);
int				draw_floor(t_data *s, t_vars v, int y, int nbr);
void			cast_floor(t_data *s, int y);

void			get_res(t_data *s, t_win *win, char *line);
void			get_texture(t_data *s, char *line, int texnbr, int i);
void			store_line(t_data *s, int fd, char *line, int i);
void			store_map(t_data *s, char *file, int start);

int				ft_kpress(int keycode, t_data *s);
int				ft_krelease(int keycode, t_data *s);
int				ft_mouse(int x, int y, t_data *s);
void			handle_movement(t_data *s);
int				render_frame(t_data *s);

int				isinv(int x, t_vec size, t_inv inv);
void			ft_get_size(t_data *s, t_vec *size, t_img *tex, double var);
void			draw_hit(t_data *s, double opc, int clr);
void			draw_flash(t_data *s);

void			draw_health(t_data *s, t_img *tex, int x, int y);
void			draw_inventory(t_data *s, t_img *tex, t_inv inv, int y);
void			draw_energy(t_data *s, t_img *tex, int x, int y);
void			draw_end(t_data *s, t_img *tex, int x, int y);
void			draw_hud(t_data *s);

void			save_pos(t_data *s, int i, int nbr);
void			init_plr(t_data *s, int nbr, double x, double y);
void			set_dir(t_data *s, int nbr);
void			set_pln(t_data *s, int nbr);

void			init_game(t_data *s, int bmp);
void			init_spr(t_data *s, int i, int nbr, t_vec pos);
void			init_tex(t_data *s);
void			init_map_and_key(t_data *s);
void			init_s(t_data *s);

void			load_texture(t_data *s, char *path, int nbr);
void			load_door_tex(t_data *s);
void			load_imgs(t_data *s);

int				check_input(t_data *s, int argc, char **argv);
int				check_adjacent_tiles(t_xy **queue, int x, int y);
int				iter_flood_fill(t_data *s, char *map, int ret, int error);
void			check_map(t_data *s);
void			is_valid(t_data *s);

void			ft_move(t_data *s, double varx, double vary, double movespeed);
void			ft_rotate(t_data *s, double var);
void			change_pitch(t_data *s, int up, double movespeed);
void			jumping(t_data *s, int jump, double movespeed);
int				movement(t_data *s, double rotspeed, double movespeed);

char			get_tile(t_data *s, int x, int y);
void			set_tile(t_data *s, int x, int y, char c);
void			skip_lines(t_data *s, char *line, int fd, int n);
int				get_nbr(char *line, int i, int *ptr);
void			get_component(t_data *s, char *line, int *ptr, int res);

void			parse_elem(t_data *s, char *line);
void			parse_map(t_data *s, char *line);
void			parse_line(t_data *s, char *line, int *start, int i);
int				skip_space(char *str);
void			parse_scene(t_data *s, char *file, int start);

t_xy			**queue_calloc(int size);
t_xy			*new_point(int x, int y);
int				add_queue(t_xy **queue, int x, int y);
void			free_queue(t_xy **xy);

void			init_sound(t_data *s);
void			play_music(t_data *s);

void			ft_sort(int *order, double *tosort, int nbr);
void			sort_sprites(t_data *s);
void			calc_sprite(t_data *s, t_vars *v);
void			draw_sprite(t_data *s, t_vars v, int nbr, t_xy start);
void			cast_sprites(t_data *s, int i);

void			store_ln_col(t_data *s, int ln, int col);
void			ft_swap(int *tab, int i);
void			ft_strfill(char *str, int i, int n);
void			ft_stricat(char *dest, char *src, int i);
int				get_snbr(t_data *s, int x, int y);

double			check_next(t_data *s, t_ray ray, t_vec pos, int side);
void			check_grid_lines(t_data *s, t_vec *ctr, int *side, int *face);
void			calc_pwd_wall(t_data *s, int side);
void			calc_pwd_door(t_data *s, t_vec ctr, int face);

void			calc_step(t_data *s);
void			find_wall(t_data *s, t_vars *v, int snbr, int x);
void			calc_slice(t_data *s, int side, int *y, int nbr);
int				draw_wall(t_data *s, int x, int side, int nbr);
void			cast_walls(t_data *s, int x);

#endif
