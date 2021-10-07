/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 07:41:38 by floogman          #+#    #+#             */
/*   Updated: 2021/03/09 11:17:42 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTING_H
# define TESTING_H

# include "../includes/libasm.h"
# include "../bonus/includes/bonus.h"

/*
** <stdio.h> to use printf
** <errno.h> to use errno identifier for ft_read and ft_write testing
** <string.h> to use str* functions
** <unistd.h> to use read and write functions
** <stdlib.h> to use free during ft_strcpy testing
** <fcntl.h> to use open function during ft_read testing
*/

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define B_RED "\033[1;31m"
# define B_GREEN "\033[1;32m"
# define B_YELLOW "\033[01;33m"
# define B_WHITE "\033[01m"
# define RESET "\033[0m"

/*
** tools.c
*/

int		compare_ints(int int_1, int int_2);
int		compare_strings(char *s1, char *s2);
void	print_comparison_result(int result);

/*
** tests.c
*/

void	test_write(int fd, char *s, int n);
void	test_read(int fd, char *buf, int n, int file);
void	test_strlen(char *test, char *s);
void	test_strcmp(char *s1, char *s2);
void	test_strcpy(char *test, char *dst, char *src);
void	test_strdup(char *test, char *s);

/*
** ft_atoi_base_c.c
*/

int		ft_atoi_base_c(char *str, char *base);

/*
** tests_bonus.c
*/

void	test_list_push_front(t_list **head, int print);
void	test_atoi_base(char *test, char *nbr, char *base);
void	test_list_remove_if(t_list **head, char *data, char *s, int print);

#endif
