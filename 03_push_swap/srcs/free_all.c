/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 08:44:04 by floogman          #+#    #+#             */
/*   Updated: 2021/05/08 07:51:50 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_all(t_info *info, char *msg)
{
	if (info->stack[A])
		free(info->stack[A]);
	if (info->stack[B])
		free(info->stack[B]);
	if (info->stack_cpy[A])
		free(info->stack_cpy[A]);
	if (info->stack_cpy[B])
		free(info->stack_cpy[B]);
	if (msg)
	{
		if (info->checker)
		{
			(info->flag_c) && ft_putstr(RED);
			ft_putstr_fd("Error: ", STDERR_FILENO);
			ft_putendl_fd(msg, STDERR_FILENO);
			(info->flag_c) && ft_putstr(RESET);
		}
		exit(1);
	}
}
