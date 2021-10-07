/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 08:31:53 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 10:43:40 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../../Libft/includes/libft.h"
# include <stdarg.h>
# include <wchar.h>
# include <ctype.h>
# include <math.h>

# define SUCCESS 0
# define FAILURE 1

typedef struct s_tab
{
	const char	*f;
	va_list		ap;
	int			len;
	size_t		i;
	long int	prec;
	long int	width;
	char		spec;
	char		flag[6];
	char		modi[4];
	char		*conv_mask;
	int			(*conv_ptr[13])(struct s_tab *);
	char		*modis;
	long double	g;
}				t_tab;

int				conv_c(t_tab *tab);
void			display_s(t_tab *tab, char *s, int len);
int				conv_s(t_tab *tab);

int				conv_d(t_tab *tab);

int				conv_e(t_tab *tab);

void			display_f(t_tab *tab, char *nbr, char *prefix);
char			*get_double(t_tab *tab, long double *d, uintmax_t *i, int k);
int				conv_f(t_tab *tab);

int				conv_p(t_tab *tab);
int				conv_n(t_tab *tab);
int				conv_g(t_tab *tab);

int				conv_u(t_tab *tab);
int				conv_x(t_tab *tab);

int				conv_ws(t_tab *tab);

void			display_wchar(t_tab *tab, wint_t c);

char			*ft_itoa_base(uintmax_t nbr, char *base, int base_size);

int				display_mod(t_tab *tab);
int				ft_printf(const char *format, ...);

char			*ft_strndup(const char *s, size_t n);

void			get_flags(t_tab *tab);
void			get_width(t_tab *tab);
void			get_precision(t_tab *tab);
void			get_modifiers(t_tab *tab);

int				padding(t_tab *tab, char c, int len, int update);
int				pre_padding(t_tab *tab, int len);

void			reinit_tab(t_tab *tab);
void			init_tab(t_tab *tab, const char *format);

int				trim_zeros(t_tab *tab, char *tmp, uintmax_t *i);
char			*get_sign(t_tab *tab, int is_neg);
int				get_len(t_tab *tab, int n_len, char *prefix);
int				display_exp(t_tab *tab, long double f);
void			display_nbr(t_tab *tab, char *nbr, char *prefix, int len);

#endif
