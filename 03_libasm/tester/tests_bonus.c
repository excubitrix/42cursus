/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 09:22:29 by floogman          #+#    #+#             */
/*   Updated: 2021/03/10 09:36:10 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

static int	print_list(t_list *head)
{
	t_list *tmp;

	tmp = head;
	while (tmp)
	{
		printf("%s -> ", (char *)tmp->data);
		tmp = tmp->next;
	}
	printf("null\n\n");
	return (0);
}

/*
** TEST: FT_LIST_PUSH_FRONT
** ----------------------------------------------------------------------------
** The strings passed to ft_list_push_front as data input are malloced,
** because ft_list_remove_if has to be able to use free on them.
*/

void		test_list_push_front(t_list **head, int print)
{
	char	*data;

	print && printf(B_YELLOW"testing ft_list_push_front"RESET"\n\n");
	data = "romeo";
	ft_list_push_front(head, strdup(data));
	data = "alpha";
	ft_list_push_front(head, strdup(data));
	data = "romeo";
	ft_list_push_front(head, strdup(data));
	data = "third";
	ft_list_push_front(head, strdup(data));
	data = "second";
	ft_list_push_front(head, strdup(data));
	data = "first";
	ft_list_push_front(head, strdup(data));
	print && printf("created list: ");
	print && print_list(*head);
}

/*
** TEST: FT_ATOI_BASE
** ----------------------------------------------------------------------------
*/

void		test_atoi_base(char *test, char *nbr, char *base)
{
	int ret[2];

	printf("testing with%s: string '%s' in base '%s'\n\n", test, nbr, base);
	ret[0] = ft_atoi_base(nbr, base);
	printf("returns \t %d\n\n", ret[0]);
	ret[1] = ft_atoi_base_c(nbr, base);
	printf("should return \t %d\n", ret[1]);
	printf("comparing results:\t\t\t\t\t");
	print_comparison_result(compare_ints(ret[0], ret[1]));
	printf("\n\n");
}

/*
** TEST: FT_LIST_REMOVE_IF
** ----------------------------------------------------------------------------
*/

void		test_list_remove_if(t_list **head, char *data, char *s, int print)
{
	printf("\nremoving '%s' from %s list\n\n", data, s);
	ft_list_remove_if(head, data, strcmp, free);
	if (print)
	{
		printf("after:\t");
		print_list(*head);
	}
	printf(B_WHITE"list size:\t%d\n"RESET, ft_list_size(*head));
}
