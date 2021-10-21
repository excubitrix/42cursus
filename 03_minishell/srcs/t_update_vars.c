/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_update_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:40:42 by mfabri            #+#    #+#             */
/*   Updated: 2021/03/21 07:15:58 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Send a VT100 escape sequence code that returns a char array with the x and y
** coordinates of the cursor. Remove the escape code from the start of the char
** array and null-terminate the array. Parse the returned string with
** ft_atoi_array to extract the coordinates.
*/

static int	update_cursor_position(t_term *trm)
{
	char	seq[32];
	int		i;
	int		*array;

	write(STDOUT_FILENO, "\x1b[6n", 4);
	i = -1;
	while (i < 32)
	{
		read(STDIN_FILENO, &seq[++i], 1);
		if (seq[i] == 'R')
			break ;
	}
	seq[0] = '-';
	seq[++i] = '\0';
	array = ft_atoi_array(seq);
	if (array[0] == -1)
		return (error_msg("update_cursor_position: ft_atoi_array"));
	trm->cursor_y = array[0];
	trm->cursor_x = array[1];
	free(array);
	return (1);
}

/*
** int index is the location of the cursor on char *line. int index_row holds
** the number of the row that index (the cursor) is on (the prompt is on row 1,
** the row beneath that is row 2, etc.). update_index_row() updates this
** number.
*/

static void	update_index_row(t_term *trm)
{
	int chars;

	trm->index_row = 1;
	chars = trm->index + trm->prompt_len;
	while ((chars - trm->scrn_cols) > 0)
	{
		chars -= trm->scrn_cols;
		trm->index_row++;
	}
}

/*
** int n_rows_line is the number of rows that char *line spans.
** update_nrows_line() updates this number.
*/

static void	update_n_rows_line(t_term *trm)
{
	int chars;

	trm->n_rows_line = 1;
	chars = ft_strlen(trm->line) + trm->prompt_len;
	while ((chars - trm->scrn_cols) > 0)
	{
		chars -= trm->scrn_cols;
		trm->n_rows_line++;
	}
}

int			update_position_trackers(t_term *trm)
{
	if (!update_cursor_position(trm))
		return (0);
	update_index_row(trm);
	update_n_rows_line(trm);
	return (1);
}
