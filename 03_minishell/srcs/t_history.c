/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_history.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:40:18 by mfabri            #+#    #+#             */
/*   Updated: 2021/03/23 11:41:02 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** - check if there is older history
** 	- if we're going from line to history, store line
** 	- move cursor to end of line (prep for removing line)
** 	- remove line
** 	- insert history entry
*/

int	get_next_history_entry(t_term *trm)
{
	if (trm->history_index > 0)
	{
		if (trm->history_len == trm->history_index)
		{
			if (trm->line_save)
				free(trm->line_save);
			if (!(trm->line_save = ft_strdup(trm->line)))
				return (error_msg("get_next_history_entry: ft_strdup"));
		}
		if (!move_cursor_to_end(trm))
			return (0);
		trm->history_index--;
		if (!remove_entire_line(trm))
			return (0);
		if (!insert_chars(trm, trm->history[trm->history_index]))
			return (0);
	}
	return (1);
}

/*
** Passed commands are added to the end of the history array. So when we press
** up to view the history, we start at the end.
**
** - check if there is more recent history
**	- move cursor to end of line (prep for removing the line)
**	- remove line
**	- if we're going from history back to the current command line, insert
**	  stored line
**	- else insert history entry
*/

int	get_previous_history_entry(t_term *trm)
{
	if (trm->history_index < trm->history_len)
	{
		trm->history_index++;
		if (!move_cursor_to_end(trm))
			return (0);
		if (!remove_entire_line(trm))
			return (0);
		if (trm->history_index == trm->history_len)
		{
			if (!insert_chars(trm, trm->line_save))
				return (0);
		}
		else if (!insert_chars(trm, trm->history[trm->history_index]))
			return (0);
	}
	return (1);
}
