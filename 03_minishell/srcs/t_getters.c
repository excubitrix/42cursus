/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_getters.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:40:15 by mfabri            #+#    #+#             */
/*   Updated: 2021/03/12 20:49:32 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_row_line_start(t_term *trm)
{
	return ((trm->cursor_y + 1) - trm->index_row);
}

/*
** Calculates the column (x coordinate) that line ends on.
*/

int	get_col_line_end(t_term *trm)
{
	int res;

	res = (ft_strlen(trm->line) + trm->prompt_len - 1)
	- ((trm->n_rows_line - 1) * trm->scrn_cols);
	return (res);
}

/*
** Calculates the row (y coordinate) that line ends on.
*/

int	get_row_line_end(t_term *trm)
{
	int res;

	res = (trm->cursor_y - 1) + (trm->n_rows_line - trm->index_row);
	return (res);
}
