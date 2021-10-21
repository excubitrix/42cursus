/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 08:31:53 by floogman          #+#    #+#             */
/*   Updated: 2020/05/02 14:41:42 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <wchar.h>
# include <ctype.h>

typedef struct	s_tab
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
	char		*convs;
	char		*flags;
	char		*modis;
	long double	g;
}				t_tab;

int				ft_printf(const char *format, ...);
t_tab			*init_tab(t_tab *tab);
void			reinit_tab(t_tab *tab);
void			get_flags(t_tab *tab);
void			get_width(t_tab *tab);
void			get_precision(t_tab *tab);
void			get_modifiers(t_tab *tab);
char			get_sign(t_tab *tab, int is_neg);
int				get_len(uintmax_t nbr);
char			*trim_zeros(char *tmp, int len);
int				dispatcher(t_tab *tab);
int				conv_c(t_tab *tab);
int				conv_s(t_tab *tab);
int				conv_d(t_tab *tab);
int				conv_p(t_tab *tab);
int				conv_u(t_tab *tab);
int				conv_x(t_tab *tab);
int				display_mod(t_tab *tab);
int				conv_n(t_tab *tab);
int				conv_f(t_tab *tab);
int				conv_g(t_tab *tab);
int				conv_e(t_tab *tab);
void			display_wchar(t_tab *tab, wint_t c);
int				conv_ws(t_tab *tab);
int				pre_padding(t_tab *tab, int len);
int				padding(t_tab *tab, char c, int len, int update);

#endif
