/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:40:45 by mfabri            #+#    #+#             */
/*   Updated: 2021/03/21 07:30:25 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** TCSAFLUSH discards any unread input
*/

int			disable_raw_mode(t_term *trm)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &trm->original_termios) == -1)
		return (0);
	return (1);
}

/*
** Free all the memory allocations made in relation to term_ctrl and disable
** raw mode.
*/

void		clear_term(t_term *trm)
{
	int i;

	i = -1;
	if (trm->history)
	{
		while (++i <= trm->history_len)
			free(trm->history[i]);
		free(trm->history);
	}
	if (trm->line_save)
		free(trm->line_save);
	if (trm->line)
		free(trm->line);
	disable_raw_mode(trm);
}

int			error_msg(char *error_message)
{
	printf("Error: %s\n", error_message);
	return (0);
}

/*
** ft_putchar variation made for use with tputs
*/

int			ft_putchar_int(int c)
{
	write(1, &c, 1);
	return (1);
}

void		print_prompt(t_term *trm, int quotes)
{
	if (trm->put_prompt == 1)
	{
		write(1, "\033[1;33m", 8);
		if (quotes)
			write(1, "> ", 3);
		else
		{
			write(1, trm->prompt, trm->prompt_len - 4);
			write(1, " > ", 4);
		}
		write(1, RESET, 5);
		trm->put_prompt = 0;
	}
}
