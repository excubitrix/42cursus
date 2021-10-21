/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_move_cursor_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:40:29 by mfabri            #+#    #+#             */
/*   Updated: 2021/03/12 20:45:53 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** - check if the command line ends on the last row of the terminal window
** - store the result of this comparison in int bottom
** - check if we haven't already reached the end of the command line
**     - if so, return, as we can't move forward
** - if the cursor is at the front of the command line and has reached the last
**   column of the terminal window
**     - write \n
** - if the cursor has reached the last column of the terminal window
**     - move it to the start of the terminal window and a row down if we're
**       not at the bottom of the screen
** - else move the cursor one space forward
*/

int	move_cursor_forward(t_term *trm)
{
	int ret;
	int bottom;

	if (trm->index == (int)ft_strlen(trm->line))
		return (1);
	bottom = get_row_line_end(trm) == trm->scrn_rows;
	if (trm->cursor_x == trm->scrn_cols && trm->index_row == trm->n_rows_line)
		write(STDOUT_FILENO, "\n", 1);
	if (trm->cursor_x == trm->scrn_cols)
		ret = tputs(tgoto(trm->tc_cursor_move
		, 0, trm->cursor_y - bottom), 1, ft_putchar_int);
	else
		ret = tputs(tgoto(trm->tc_cursor_move
		, trm->cursor_x, trm->cursor_y - (1 + bottom)), 1, ft_putchar_int);
	if (ret == ERR)
		return (error_msg("move_cursor_forward: tputs"));
	trm->index++;
	trm->cursor_x++;
	return (1);
}

/*
** - check if we can move backwards
** 	- check if the cursor needs to go to the end of the previous row
** 	- else the cursor just needs to go one to the left
*/

int	move_cursor_back(t_term *trm)
{
	int ret;

	if (trm->index > 0
	&& !(trm->index_row == 1 && trm->cursor_x == trm->prompt_len))
	{
		if (trm->cursor_x == 1)
			ret = tputs(tgoto(trm->tc_cursor_move, trm->scrn_cols - 1
			, trm->cursor_y - 2), 1, ft_putchar_int);
		else
			ret = tputs(tgoto(trm->tc_cursor_move, trm->cursor_x - 2
			, trm->cursor_y - 1), 1, ft_putchar_int);
		if (ret == ERR)
			return (error_msg("move_cursor_back: tputs"));
		trm->cursor_x--;
		trm->index--;
		return (1);
	}
	return (2);
}

/*
** - check if there is any input on the command line
** 	- move cursor to end of command line
** 	- update position trackers
*/

int	move_cursor_to_end(t_term *trm)
{
	if (ft_strlen(trm->line) != 0)
	{
		if (tputs(tgoto(trm->tc_cursor_move, get_col_line_end(trm)
		, get_row_line_end(trm)), 1, ft_putchar_int) == ERR)
			return (error_msg("move_cursor_to_end: tputs"));
		trm->index = ft_strlen(trm->line);
		if (!update_position_trackers(trm))
			return (0);
	}
	return (1);
}

int	move_cursor_to_start(t_term *trm)
{
	if (ft_strlen(trm->line) != 0 && trm->index != 0)
	{
		if (tputs(tgoto(trm->tc_cursor_move, trm->prompt_len - 1
		, get_row_line_start(trm) - 1), 1, ft_putchar_int) == ERR)
			return (error_msg("move_cursor_to_start: tputs"));
		trm->index = 0;
		if (!update_position_trackers(trm))
			return (0);
	}
	return (1);
}
