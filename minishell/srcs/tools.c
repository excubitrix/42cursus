/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 09:31:18 by floogman          #+#    #+#             */
/*   Updated: 2021/03/26 07:36:21 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Implementation of the isatty() function.
** "The isatty() function determines if the file descriptor fd refers to a valid
** terminal type device."
** It is used to check if the input is being pipe'd into minishell.
*/

int		ft_isatty(int fd)
{
	struct termios	term;

	return (tcgetattr(fd, &term) == 0);
}

/*
** Checks if the int passed matches one of the following characters: less-than,
** greater-than, "right shift".
*/

int		is_redir(int c)
{
	if (c == '<' || c == '>' || c == '>' + 1)
		return (c);
	return (0);
}

/*
** Checks if the int passed matches one of the following characters:
** single quote, double quote, escape sign, space, null, ampersand, semicolon,
** pipe, greater-than, less-than.
*/

int		get_type(int c)
{
	if (c == '\'' || c == '\"' || c == '\\' || c == ' ' || c == '\0'
		|| c == '&' || c == ';' || c == '|' || c == '>' || c == '<')
		return (c);
	return (-1);
}

/*
** Checks the status of the fd passed. Used by open_file_out().
*/

int		check_fd_stat(int fd)
{
	struct stat		buf;

	if (fstat(fd, &buf) < 0)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putnbr_fd(fd, STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putendl_fd(strerror(errno), STDERR);
		close(fd);
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
** A mini ft_strjoin that frees the strings it is passed even on error.
*/

char	*mini_strjoin(char *s1, char *s2, char *link)
{
	int		len;
	char	*ret;

	if (s1 && !s2)
	{
		free(s1);
		return (NULL);
	}
	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + 1 + ft_strlen(s2);
	if (!(ret = malloc(len + 1)))
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	ret[0] = '\0';
	ret = ft_strcat(ret, (char *)s1);
	if (link != NULL)
		ret = ft_strcat(ret, link);
	ret = ft_strcat(ret, (char *)s2);
	free(s1);
	free(s2);
	return (ret);
}
