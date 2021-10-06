/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 13:17:35 by floogman          #+#    #+#             */
/*   Updated: 2021/10/06 10:37:24 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus/get_next_line_bonus.h"
#include <fcntl.h> // open
#include <string.h> // strncmp
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd1;
	int		fd2;
	int		tmp;
	int		ret;
	int		count;
	char	*line;

	if (argc == 1)
	{
		while (get_next_line(0, &line) == 1)
		{
			if (line && !strncmp(line, "exit", 4))
				break ;
			printf("%s\n", line);
			free(line);
		}
		return (0);
	}
	else if (argc != 3)
		return (-1);
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	count = 0;
	tmp = fd1;
	while ((ret = get_next_line(tmp, &line)) != -1)
	{
		printf("%s\n", line);
		free(line);
		tmp = fd2;
		if (count++ % 2)
			tmp = fd1;
		if (!ret && !get_next_line(tmp, &line))
			break;
	}
	printf("%s", line);
	free(line);
	close(fd1);
	close(fd2);
	return (0);
}
