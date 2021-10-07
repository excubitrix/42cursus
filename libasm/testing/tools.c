/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 07:40:43 by floogman          #+#    #+#             */
/*   Updated: 2021/03/09 08:07:54 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

int		compare_ints(int int_1, int int_2)
{
	return (int_1 == int_2);
}

int		compare_strings(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((s1[i] - s2[i]) == 0);
}

void	print_comparison_result(int result)
{
	if (result)
		printf(B_GREEN"OK "RESET);
	else
	{
		printf(B_RED"KO"RESET" (exiting)");
		exit(0);
	}
}
