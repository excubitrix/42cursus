/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_line_manip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:40:26 by mfabri            #+#    #+#             */
/*   Updated: 2021/03/21 07:25:16 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** - check if there is something to remove
** 	- move cursor to just after prompt
** 	- remove everything after cursor
** 	- empty line
*/

int	remove_entire_line(t_term *trm)
{
	if (trm->line[0])
	{
		if (!move_cursor_to_start(trm))
			return (0);
		ft_putstr_fd(trm->tc_remove_all_after_cursor, STDOUT_FILENO);
		if (!init_line(&trm->line))
			return (0);
		trm->index = 0;
	}
	return (1);
}

/*
** - check if there's something to backspace and move cursor back
**     - if cursor can't move back, return
** - make cursor invisible
** - remove character at location of cursor
** - save cursor position
** - instead of shortening the string, we stick a space at the end, so that the
**   character that was there before is overwritten with the space when line is
**   rewritten to the screen
** - restore cursor position
** - remove the space as it has done its job
** - make cursor visible again
*/

int	remove_char(t_term *trm)
{
	int ret;
	int len;

	if ((ret = move_cursor_back(trm)) != 1)
		return (ret);
	if (!update_position_trackers(trm))
		return (0);
	if (tputs(trm->tc_cursor_invisible, 1, ft_putchar_int) == ERR)
		return (error_msg("remove_char: tputs"));
	len = ft_strlen(trm->line);
	if (!ft_memmove(&trm->line[trm->index], &trm->line[trm->index + 1]
	, len - trm->index))
		return (error_msg("remove_char: ft_memmove"));
	trm->line[len - 1] = ' ';
	trm->line[len] = '\0';
	ft_putstr_fd(trm->tc_store_cursor_position, STDOUT_FILENO);
	ft_putstr(trm->line + trm->index);
	ft_putstr_fd(trm->tc_restore_cursor_position, STDOUT_FILENO);
	trm->line[len - 1] = '\0';
	if (tputs(trm->tc_cursor_visible, 1, ft_putchar_int) == ERR)
		return (error_msg("remove_char: tputs"));
	return (ret);
}

int	insert_string(t_term *trm, char *s)
{
	if (trm->line)
		free(trm->line);
	if (!(trm->line = ft_strdup(s)))
		return (error_msg("insert_string: ft_strdup"));
	ft_putstr(trm->line + trm->index);
	trm->index = ft_strlen(trm->line);
	return (1);
}

/*
** - make cursor invisible to avoid flicker-jumping
** - allocate additional space for line
** - move the content after index one space back
** - insert the character at the location of index
** - print line, starting from the cursor, to update it on the screen
** - move cursor one space forward from where it was before printing line
** - make cursor visible again
*/

int	insert_chars(t_term *trm, char *buf)
{
	int i;

	i = -1;
	while (buf[++i] && ft_isprint(buf[i]))
	{
		if (tputs(trm->tc_cursor_invisible, 1, ft_putchar_int) == ERR)
			return (error_msg("insert_char: tputs"));
		if (!(trm->line = ft_realloc(trm->line, ft_strlen(trm->line) + 2)))
			return (error_msg("insert_char: ft_realloc"));
		if (!(ft_memmove(&trm->line[trm->index + 1], &trm->line[trm->index]
		, ft_strlen(trm->line) - trm->index + 1)))
			return (error_msg("insert_char: ft_memmove"));
		trm->line[trm->index] = buf[i];
		ft_putstr(trm->line + trm->index);
		if (!move_cursor_forward(trm))
			return (0);
		if (tputs(trm->tc_cursor_visible, 1, ft_putchar_int) == ERR)
			return (error_msg("insert_char: tputs"));
		if (!update_position_trackers(trm))
			return (-1);
	}
	return (1);
}
