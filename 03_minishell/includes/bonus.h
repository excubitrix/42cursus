/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:33:11 by floogman          #+#    #+#             */
/*   Updated: 2021/03/24 08:04:35 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "minishell.h"
# include "../libft/includes/libft.h"
# include <glob.h>

int			wildcard_expansion(t_info *info, glob_t globbuf);

#endif
