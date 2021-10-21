/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_initialise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:40:23 by mfabri            #+#    #+#             */
/*   Updated: 2021/03/27 08:22:02 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** - store the original termios attributes
** - turn off echo: keys will no longer be printed to the terminal
**   automatically
** - turn off ICANON: input is read byte-by-byte instead of line-by-line
** - turn off ISIG: signals are disabled: ctrl-C can be read as 3, ctrl-D as 4
**   and ctrl-\ as 28
*/

int			enable_raw_mode(t_term *trm)
{
	struct termios raw;

	if (tcgetattr(STDIN_FILENO, &trm->original_termios) == -1)
		return (error_msg("enable_raw_mode: tcgetattr"));
	raw = trm->original_termios;
	raw.c_lflag &= ~(ECHO | ICANON | ISIG);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		return (error_msg("enable_raw_mode: tcsetattr"));
	return (1);
}

int			init_line(char **line)
{
	if (*line)
		free(*line);
	if (!(*line = malloc(1)))
		return (error_msg("init_line: malloc"));
	*line[0] = '\0';
	return (1);
}

static int	init_termcaps(t_term *trm)
{
	if (!(trm->tc_cursor_move = tgetstr("cm", NULL))
	|| !(trm->tc_cursor_move_to_col = tgetstr("ch", NULL))
	|| !(trm->tc_remove_all_after_cursor = tgetstr("cd", NULL))
	|| !(trm->tc_cursor_invisible = tgetstr("vi", NULL))
	|| !(trm->tc_cursor_visible = tgetstr("ve", NULL))
	|| !(trm->tc_store_cursor_position = tgetstr("sc", NULL))
	|| !(trm->tc_restore_cursor_position = tgetstr("rc", NULL)))
		return (error_msg("init_termcaps: tgetstr"));
	return (1);
}

int			init_term(t_term *trm, char *env)
{
	trm->line = NULL;
	trm->line_save = NULL;
	trm->history = NULL;
	trm->put_prompt = 1;
	trm->index = 0;
	if (tgetent(NULL, env) < 1)
		return (error_msg("init_term: tgetent"));
	trm->initialised = 1;
	if ((trm->scrn_cols = tgetnum("co")) == -1
	|| (trm->scrn_rows = tgetnum("li")) == -1)
		return (error_msg("init_term: tgetnum"));
	if (!(trm->history = malloc(sizeof(char *) * 1)))
		return (error_msg("init_term: malloc"));
	trm->history[0] = NULL;
	trm->history_len = 0;
	trm->history_index = 0;
	if (!init_line(&trm->line)
	|| !init_termcaps(trm))
		return (0);
	return (1);
}
