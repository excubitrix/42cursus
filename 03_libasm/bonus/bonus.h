/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 12:18:34 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 13:02:13 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "../includes/libasm.h"

typedef struct		s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

int					ft_atoi_base(char *str, char *base);
void				ft_list_push_front(t_list **begin_list, void *data);
void				ft_list_remove_if(t_list **begin_list, void *data_ref,
						int(*cmp)(), void(*free_fct)(void*));
int					ft_list_size(t_list *begin_list);
void				ft_list_sort(t_list **begin_list, int(*cmp)());

#endif
