/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:00:01 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:51:13 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int			get_next_line(int fd, char **line);

size_t		gnl_strlen(const char *s);
int			gnl_strchr(const char *s, int c);
char		*gnl_strndup(char *s1, int n);
char		*gnl_strsubdup(char *s, int start, int end);
char		*gnl_strjoin(char *s1, char const *s2);

#endif
