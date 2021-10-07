/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:59:13 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:50:49 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_abort(char *s)
{
	if (s)
		free(s);
	return (-1);
}

static int	do_line(char **s, char **line, int index)
{
	int	len;

	len = gnl_strlen(*s);
	*line = gnl_strndup(*s, index);
	if (!*line)
		return (ft_abort(*s));
	if (index >= 0)
	{
		*s = gnl_strsubdup(*s, index + 1, len);
		if (!*s)
			return (ft_abort(*s));
		return (1);
	}
	free(*s);
	*s = NULL;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*s[OPEN_MAX];
	int			bytes;

	if (fd > OPEN_MAX || fd < 0 || !line)
		return (-1);
	bytes = read(fd, &buf, BUFFER_SIZE);
	while (bytes > 0)
	{
		buf[bytes] = '\0';
		if (!s[fd])
			s[fd] = gnl_strndup(buf, bytes);
		else
			s[fd] = gnl_strjoin(s[fd], buf);
		if (!s[fd])
			return (-1);
		if (gnl_strchr(s[fd], '\n') != -1)
			break ;
		bytes = read(fd, &buf, BUFFER_SIZE);
	}
	if (bytes < 0)
		return (ft_abort(s[fd]));
	return (do_line(&s[fd], line, gnl_strchr(s[fd], '\n')));
}
