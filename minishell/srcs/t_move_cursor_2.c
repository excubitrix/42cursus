/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_move_cursor_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:40:35 by mfabri            #+#    #+#             */
/*   Updated: 2021/03/12 20:44:39 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** - check if cursor can move straight up
** 	- yes, cursor moves straight up
** - no, move cursor to start of line
*/

int	move_cursor_up(t_term *trm)
{
	if (trm->index - trm->scrn_cols >= 0)
	{
		if (tputs(tgoto(trm->tc_cursor_move, trm->cursor_x - 1
		, trm->cursor_y - 2), 1, ft_putchar_int) == ERR)
			return (error_msg("move_cursor_up: tputs"));
		trm->index -= trm->scrn_cols;
		if (!update_position_trackers(trm))
			return (0);
	}
	else if (!move_cursor_to_start(trm))
		return (0);
	return (1);
}

/*
** - check if cursor can move straight down
**	- yes, move cursor straight down
** - no, move cursor to end of line
*/

int	move_cursor_down(t_term *trm)
{
	if (trm->index + trm->scrn_cols <= (int)ft_strlen(trm->line))
	{
		if (tputs(tgoto(trm->tc_cursor_move, trm->cursor_x - 1
		, trm->cursor_y), 1, ft_putchar_int) == ERR)
			return (error_msg("move_cursor_down: tputs"));
		trm->index += trm->scrn_cols;
		if (!update_position_trackers(trm))
			return (0);
	}
	else if (!move_cursor_to_end(trm))
		return (0);
	return (1);
}

/*
** - check if cursor is not on row 1
** 	- yes, move cursor to start of row
** - no, move cursor to start of line
*/

int	move_cursor_to_start_of_row(t_term *trm)
{
	if (trm->index_row > 1)
	{
		if (tputs(tgoto(trm->tc_cursor_move, 0
		, trm->cursor_y - 1), 1, ft_putchar_int) == ERR)
			return (error_msg("move_cursor_to_start_of_row: tputs"));
		trm->index -= trm->cursor_x - 1;
		if (!update_position_trackers(trm))
			return (0);
	}
	else if (!move_cursor_to_start(trm))
		return (0);
	return (1);
}

/*
** - check if cursor is on the same row that line ends on and if line ends
**   before the last column
**     - yes, move cursor to end of line
** - no, move cursor to end of row
*/

int	move_cursor_to_end_of_row(t_term *trm)
{
	if (trm->n_rows_line == trm->index_row
	&& get_col_line_end(trm) < trm->scrn_cols)
	{
		if (!move_cursor_to_end(trm))
			return (0);
	}
	else
	{
		if (tputs(tgoto(trm->tc_cursor_move, trm->scrn_cols - 1
		, trm->cursor_y - 1), 1, ft_putchar_int) == ERR)
			return (error_msg("move_cursor_to_end_of_row: tputs"));
		trm->index += trm->scrn_cols - trm->cursor_x;
		if (!update_position_trackers(trm))
			return (0);
	}
	return (1);
}
