/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:40:49 by mfabri            #+#    #+#             */
/*   Updated: 2021/03/21 08:34:35 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Arrow keys send multiple byte codes starting with the escape code \x1b. This
** escape code has already been stripped off when we arrive in this function.
** The next byte is '[', and then a letter which indicates the direction.
*/

static int	process_arrow_keys(t_term *trm, char *buf)
{
	int		ret;

	ret = 1;
	if (buf[2] == 'A')
		ret = get_next_history_entry(trm);
	else if (buf[2] == 'B')
		ret = get_previous_history_entry(trm);
	else if (buf[2] == 'C')
		ret = move_cursor_forward(trm);
	else if (buf[2] == 'D')
		ret = move_cursor_back(trm);
	else if (buf[2] == '1' && buf[3] == ';' && buf[4] == '2')
	{
		if (buf[5] == 'A')
			ret = move_cursor_up(trm);
		else if (buf[5] == 'B')
			ret = move_cursor_down(trm);
		else if (buf[5] == 'C')
			ret = move_cursor_to_end_of_row(trm);
		else if (buf[5] == 'D')
			ret = move_cursor_to_start_of_row(trm);
	}
	return (ret);
}

/*
** Enter has been pressed, so we
** - duplicate the command line input to the address that was given by loop()
** - store the command line input as history
** - move to a new line
** - return the number of bytes of the command line input
*/

static int	process_enter(t_term *trm, char **line)
{
	if (!move_cursor_to_end(trm))
		return (-1);
	if (!(*line = ft_strdup(trm->line)))
		return (-1);
	if (trm->line[0])
	{
		if (!(trm->history = tab_add(trm->history, trm->line)))
		{
			error_msg("process_enter: tab_add");
			return (-1);
		}
		trm->history_len++;
	}
	trm->history_index = trm->history_len;
	trm->put_prompt = 1;
	if (!init_line(&trm->line))
		return (-1);
	trm->index = 0;
	write(1, "\n", 1);
	return (ft_strlen(*line));
}

static int	process_ctrl_char(t_term *trm, char *buf)
{
	int ret;

	ret = 1;
	if (buf[0] == KEY_BCKSPACE)
		ret = remove_char(trm);
	else if (buf[0] == KEY_CTRL_C)
	{
		write(1, "\n", 1);
		sig_handler(SIGINT);
		ret = init_line(&trm->line);
		trm->history_index = trm->history_len;
		trm->index = 0;
		trm->put_prompt = 1;
	}
	else if (buf[0] == KEY_CTRL_D && !trm->line[0])
		return (0);
	else if (buf[0] == KEY_CTRL_U)
		ret = remove_entire_line(trm);
	else if (buf[0] == KEY_ESC && buf[1] == '[')
		ret = process_arrow_keys(trm, buf);
	else if (buf[0] == KEY_ARROW_L)
		ret = move_cursor_to_start(trm);
	else if (buf[0] == KEY_ARROW_R)
		ret = move_cursor_to_end(trm);
	return (ret);
}

/*
** read() only reads 50 bytes at a time (for unknown reasons). If more bytes
** are entered at once (e.g. by pasting), these bytes are 'placed in a queue'
** and will be read the next time read() is called. This is problematic when
** you want to use read() to read something else in the meantime, which is the
** case here. Therefore, we read bytes with read() into a "dump" buffer until
** the queue is empty.
*/

int			term_ctrl(t_term *trm, char **line, int quotes)
{
	char	buf[51];
	char	dump[50];
	int		bytes;

	if (!enable_raw_mode(trm))
		return (-1);
	while (1)
	{
		print_prompt(trm, quotes);
		if (!update_position_trackers(trm))
			return (-1);
		ft_memset(buf, 0, 51);
		if ((bytes = read(STDIN, buf, 50)) == -1)
			return (-1);
		while (bytes == 50)
			if ((bytes = read(STDIN, dump, 50)) == -1)
				return (-1);
		if (ft_isprint(buf[0]) && !insert_chars(trm, buf))
			return (-1);
		else if (buf[0] == KEY_RETURN)
			return (process_enter(trm, line));
		else if (!ft_isprint(buf[0]) && !process_ctrl_char(trm, buf))
			return (-1);
	}
	return (1);
}
