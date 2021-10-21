/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 12:19:14 by floogman          #+#    #+#             */
/*   Updated: 2021/03/09 08:49:44 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

/*
** TEST: FT_READ
** ----------------------------------------------------------------------------
*/

void	test_read(int fd, char *buf, int n, int file)
{
	int		err[2];
	int		ret[2];

	file ? fd = open("testing/file.txt", O_RDONLY) : fd;
	printf("testing with (%d, %s, %d)\n", fd, buf, n);
	ret[0] = (int)ft_read(fd, buf, n);
	err[0] = errno;
	printf("<libasm> returns:\t%d\nbuf contains:\t\t'%s'\n", ret[0], buf);
	if (ret[0] < 0)
		printf("errno is\t\t%d (%s)\n", err[0], strerror(err[0]));
	file && close(fd);
	file ? fd = open("testing/file.txt", O_RDONLY) : fd;
	ret[1] = (int)read(fd, buf, n);
	err[1] = errno;
	printf("<unistd> returns:\t%d\nbuf contains:\t\t'%s'\n", ret[1], buf);
	if (ret[1] < 0)
		printf("errno should be\t\t%d (%s)\n", err[1], strerror(err[1]));
	file && close(fd);
	printf("comparing results (and errno if applicable):\t\t");
	print_comparison_result(compare_ints(ret[0], ret[1]));
	if (ret[0] == -1)
		print_comparison_result(compare_ints(err[0], err[1]));
	printf("\n\n");
}

/*
** TEST: FT_STRLEN
** ----------------------------------------------------------------------------
** strlen and ft_strlen both segfaults when NULL is passed as arg
*/

void	test_strlen(char *test, char *s)
{
	long unsigned int	ret[2];

	printf("testing with%s: \t'%s'\n", test, s);
	ret[0] = ft_strlen(test);
	printf("<libasm> returns:\t%lu\n", ret[0]);
	ret[1] = strlen(test);
	printf("<unistd> returns:\t%lu\n", ret[1]);
	printf("comparing results:\t\t\t\t\t");
	print_comparison_result(compare_ints(ret[0], ret[1]));
	printf("\n\n");
}

/*
** TEST: FT_STRCMP
** ----------------------------------------------------------------------------
** strcmp and ft_strcmp both segfaults when NULL is passed as arg
*/

void	test_strcmp(char *s1, char *s2)
{
	int		ret[2];

	printf("testing with '%s' and '%s'\n", s1, s2);
	ret[0] = ft_strcmp(s1, s2);
	printf("<libasm> returns: \t%d\n", ret[0]);
	ret[1] = strcmp(s1, s2);
	printf("<unistd> returns: \t%d\n", ret[1]);
	printf("comparing results:\t\t\t\t\t");
	print_comparison_result(compare_ints(ret[0], ret[1]));
	printf("\n\n");
}

/*
** TEST: FT_STRCPY
** ----------------------------------------------------------------------------
** strcpy and ft_strcpy both segfault when NULL is passed as src
*/

void	test_strcpy(char *test, char *dst, char *src)
{
	char	*ret[2];

	printf("testing with%s: \t'%s'\n", test, src);
	ret[0] = ft_strcpy(dst, src);
	printf("<libasm> returns: \t'%s'\n", ret[0]);
	ret[1] = strcpy(dst, src);
	printf("<unistd> returns: \t'%s'\n", ret[1]);
	printf("comparing results:\t\t\t\t\t");
	print_comparison_result(compare_strings(ret[0], ret[1]));
	printf("\n\n");
}

/*
** TEST: FT_STRDUP
** ----------------------------------------------------------------------------
** strdup and ft_strdup both segfault when NULL is passed as an arg
*/

void	test_strdup(char *test, char *s)
{
	char	*ret[2];

	printf("testing with%s: \t'%s'\n", test, s);
	ret[0] = ft_strdup(s);
	printf("<libasm> returns: \t'%s'\n", ret[0]);
	ret[1] = strdup(s);
	printf("<unistd> returns: \t'%s'\n", ret[1]);
	printf("comparing results:\t\t\t\t\t");
	print_comparison_result(compare_strings(ret[0], ret[1]));
	printf("\n\n");
	free(ret[0]);
	free(ret[1]);
}
