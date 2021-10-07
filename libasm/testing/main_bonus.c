/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 13:06:35 by floogman          #+#    #+#             */
/*   Updated: 2021/03/09 11:58:44 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

static void	print_list(t_list *head)
{
	t_list *tmp;

	tmp = head;
	while (tmp)
	{
		printf("%s -> ", (char *)tmp->data);
		tmp = tmp->next;
	}
	printf("null\n\n");
}

static void	testing_atoi_base(void)
{
	printf(B_YELLOW"\ntesting ft_atoi_base\n\n"RESET);
	test_atoi_base("decimal", "123", "0123456789");
	test_atoi_base("' \\t-+-+123- '", " \t-+-+123- ", "0123456789");
	test_atoi_base("' \\t-+-+-123- '", " \t-+-+-123- ", "0123456789");
	test_atoi_base("' -\\t-+-+-123- '", " -\t-+-+-123- ", "0123456789");
	test_atoi_base("int max", "2147483647", "0123456789");
	test_atoi_base("int max + 1", "2147483648", "0123456789");
	test_atoi_base("int min", "-2147483648", "0123456789");
	test_atoi_base("int min - 1", "-2147483649", "0123456789");
	test_atoi_base("binary", "123", "01");
	test_atoi_base("binary", "10101", "01");
	test_atoi_base("hexadecimal", "ff", "0123456789abcdef");
	test_atoi_base("empty string", "", "0123456789");
	test_atoi_base("no chars from base in string", "test", "0123456789");
	test_atoi_base("string equals \\0", "\0", "0123456789");
	test_atoi_base("base equals \\0", "123", "\0");
	test_atoi_base("string and base equal \\0", "\0", "\0");
	test_atoi_base("base with a dublicate char", "123", "01234567890");
	test_atoi_base("base with a space", "123", "01234 56789");
	test_atoi_base("base with a sign", "123", "01234-56789");
	test_atoi_base("an empty base", "123", "");
	test_atoi_base("base with a size of 1", "1", "1");
}

static int	part2(int argc, char **argv, t_list *head)
{
	t_list	*empty;

	empty = NULL;
	if (argc == 1 || !(strcmp(argv[1], "ft_list_sort")))
	{
		printf(B_YELLOW"testing ft_list_sort\n\n"RESET);
		ft_list_sort(&head, strcmp);
		printf("sorted list:\t");
		print_list(head);
		ft_list_sort(&empty, strcmp);
		ft_list_sort(NULL, strcmp);
	}
	if (argc == 1 || !(strcmp(argv[1], "ft_list_remove_if")))
	{
		printf(B_YELLOW"testing ft_list_remove_if"RESET"\n");
		test_list_remove_if(&head, "first", "the", 1);
		test_list_remove_if(&head, "", "the", 1);
		test_list_remove_if(&head, "romeo", "the", 1);
		test_list_remove_if(&empty, "test", "an empty", 0);
	}
	if (argc == 1 || !(strcmp(argv[1], "ft_atoi_base")))
		testing_atoi_base();
	system("leaks out_bonus > leaks_bonus.txt");
	return (0);
}

int			main(int argc, char **argv)
{
	t_list *head;

	head = NULL;
	if (argc == 1 || !(strcmp(argv[1], "ft_list_push_front")))
		test_list_push_front(&head, 1);
	else
		test_list_push_front(&head, 0);
	if (argc == 1 || !(strcmp(argv[1], "ft_list_size")))
	{
		printf(B_YELLOW"testing ft_list_size"RESET"\n\n");
		printf(B_WHITE"list size:\t%d\n\n"RESET, ft_list_size(head));
	}
	part2(argc, argv, head);
	return (0);
}
