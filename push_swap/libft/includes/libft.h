/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 09:31:18 by floogman          #+#    #+#             */
/*   Updated: 2021/04/13 12:51:02 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_isdigit(int c);
int				ft_isspace(int c);
int				ft_max(int a, int b);
int				ft_min(int a, int b);
int				ft_putchar_fd(char c, int fd);
int				ft_putchar(char c);
int				ft_putendl_fd(char *s, int fd);
int				ft_putnbr_endl(int n);
int				ft_putnbr_fd(int n, int fd);
int				ft_putnbr(int n);
int				ft_putstr_endl(char *s);
int				ft_putstr_fd(char *s, int fd);
int				ft_putstr(char *s);
int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
