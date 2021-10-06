/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 13:17:35 by floogman          #+#    #+#             */
/*   Updated: 2021/10/06 10:37:27 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h> // open
#include <string.h> // strncmp
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
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
	else if (argc != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		printf("%s\n", line);
		free(line);
	}
	printf("%s", line);
	/* ~ for easier output comparison ~ */
	if (line && !strncmp(line, "", 1))
		printf("\n");
	/* ~~ with a buffer size of zero ~~ */
	free(line);
	close(fd);
	return (0);
}
