/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 09:14:20 by floogman          #+#    #+#             */
/*   Updated: 2021/03/10 09:45:02 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

static int	part3(int argc, char **argv)
{
	char *dst;

	dst = strdup("                        ");
	if (argc == 1 || !(strcmp(argv[1], "ft_strcpy")))
	{
		printf(B_YELLOW"testing ft_strcpy\n\n"RESET);
		test_strcpy(" an empty string", dst, "");
		test_strcpy(" only a space", dst, " ");
		test_strcpy(" only a \\n", dst, "\n");
		test_strcpy(" only a \\0", dst, "\0");
		test_strcpy("", dst, "testing: 1, 2, 3...");
	}
	free(dst);
	if (argc == 1 || !(strcmp(argv[1], "ft_strdup")))
	{
		printf(B_YELLOW"testing ft_strdup\n\n"RESET);
		test_strdup(" an empty string", "");
		test_strdup(" only \\0", "\0");
		test_strdup(" only \\0", "\0");
		test_strdup("", "testing: 1, 2, 3");
	}
	system("leaks out > leaks.txt");
	return (0);
}

static int	part2(int argc, char **argv)
{
	if (argc == 1 || !(strcmp(argv[1], "ft_strlen")))
	{
		printf(B_YELLOW"testing ft_strlen\n\n"RESET);
		test_strlen(" \\n in string", "testing: 1, 2, 3...\n 4, 5, 6...");
		test_strlen(" \\0 in string", "testing: 1, 2, 3...\0 4, 5, 6...");
		test_strlen(" an empty string", "");
		test_strlen(" only a \\n", "\n");
		test_strlen(" only a \\0", "\0");
	}
	if (argc == 1 || !(strcmp(argv[1], "ft_strcmp")))
	{
		printf(B_YELLOW"testing ft_strcmp\n\n"RESET);
		test_strcmp("abc", "abc");
		test_strcmp("abc", "abcd");
		test_strcmp("abz", "ab");
		test_strcmp("", "");
		test_strcmp("\0", "\0");
	}
	part3(argc, argv);
	return (0);
}

int			main(int argc, char **argv)
{
	char	buf[99];

	if (argc == 1 || !(strcmp(argv[1], "ft_write")))
	{
		printf(B_YELLOW"testing ft_write\n\n"RESET);
		test_write(1, "abc", 0);
		test_write(1, "abc", 1);
		test_write(1, "abc", 10);
		test_write(1, "", 5);
		test_write(1, NULL, 5);
		test_write(-1, "abc", 10);
		test_write(OPEN_MAX + 1, "abc", 3);
	}
	if (argc == 1 || !(strcmp(argv[1], "ft_read")))
	{
		printf(B_YELLOW"testing ft_read\n\n"RESET);
		test_read(0, buf, 0, 1);
		test_read(0, buf, 10, 1);
		test_read(0, buf, 5, 1);
		test_read(-1, buf, 1, 0);
		test_read(OPEN_MAX + 1, buf, 1, 0);
		test_read(0, NULL, 5, 1);
	}
	part2(argc, argv);
	return (0);
}

/*
** TEST: FT_WRITE
** ----------------------------------------------------------------------------
*/

void		test_write(int fd, char *s, int n)
{
	int		err[2];
	int		ret[2];

	printf("testing with (%d, %s, %d)\n", fd, s, n);
	ret[0] = (int)ft_write(fd, s, n);
	err[0] = errno;
	printf(" | <libasm> returns:\t%d\n", ret[0]);
	if (ret[0] < 0)
		printf("errno is\t\t%d (%s)\n", err[0], strerror(err[0]));
	ret[1] = (int)write(fd, s, n);
	err[1] = errno;
	printf(" | <unistd> returns:\t%d\n", ret[1]);
	if (ret[1] < 0)
		printf("errno should be\t\t%d (%s)\n", err[1], strerror(err[1]));
	printf("comparing results (and errno if applicable):\t\t");
	print_comparison_result(compare_ints(ret[0], ret[1]));
	if (ret[0] == -1)
		print_comparison_result(compare_ints(err[0], err[1]));
	printf("\n\n");
}
