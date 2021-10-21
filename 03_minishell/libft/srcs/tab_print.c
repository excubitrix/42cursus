/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 13:22:31 by floogman          #+#    #+#             */
/*   Updated: 2021/03/18 10:53:01 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		tab_print(char **tab, char sep)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%s%c", tab[i], sep);
		i++;
	}
	ft_printf("%s", tab[i]);
	ft_printf("\n");
	return (0);
}
