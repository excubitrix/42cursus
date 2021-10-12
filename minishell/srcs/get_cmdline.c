/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 18:30:53 by floogman          #+#    #+#             */
/*   Updated: 2021/03/25 12:49:15 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Frees the string pointed to by char *tofree before returning.
*/

static int	ft_abort(char *tofree)
{
	if (tofree)
		free(tofree);
	return (-1);
}

/*
** Reads a line from stdin and saves it.
*/

int			get_line(char **line, int bytes)
{
	char	*s;
	char	buf[1];
	int		ret;
	int		i;

	if (!(s = malloc(sizeof(char) * (BUFSIZE + 1))))
		return (-1);
	while ((ret = read(STDIN, &buf, 1)) > 0 && buf[0] != '\n')
		s[bytes++] = buf[0];
	if (!ret && !bytes)
		return (ft_abort(s));
	if (!(*line = malloc(sizeof(char) * (bytes + 1))))
		return (ft_abort(s));
	i = -1;
	while (++i < bytes)
		(*line)[i] = s[i];
	(*line)[i] = '\0';
	free(s);
	return (bytes);
}

/*
** Checks if all quotes have a match.
*/

static int	check_quotes(char *s, int i, int quote)
{
	while (s && s[i])
	{
		if (quote != 1)
		{
			if (!quote && s[i] == '\'')
				quote = 1;
			if (!quote && s[i] == '\"')
				quote = 2;
			else if (quote == 2 && s[i] == '\"')
				quote = 0;
			if (s[i] == '\\')
				i++;
		}
		else if (s[i] == '\'')
			quote = 0;
		i++;
	}
	if (quote)
		return (FAILURE);
	return (SUCCESS);
}

/*
** Puts the error message to the screen if a line that was
** piped to minishell is missing a matching quote.
*/

static void	put_quote_error(t_info *info, int quote)
{
	ft_putstr_fd("minishell: unexpected ", STDERR);
	ft_putstr_fd("EOF while looking for matching `", STDERR);
	if (quote < 0)
		ft_putendl_fd("\'", STDERR);
	else
		ft_putendl_fd("\"", STDERR);
	info->ret = SYNTAX_ERR;
	ft_exit(info, NULL);
}

/*
** Entry point for retrieving input.
*/

void		get_cmdline(t_info *info, int not_pipe)
{
	char	*next;
	int		quote;

	if (not_pipe)
	{
		if (term_ctrl(info->trm_ptr, &info->line, 0) < 0)
			ctrl_d(info);
		if (!disable_raw_mode(info->trm_ptr))
			ft_exit(info, NULL);
	}
	else if (get_line(&info->line, 0) < 0)
		ft_exit(info, NULL);
	while ((quote = check_quotes(info->line, 0, 0)))
	{
		if (!not_pipe)
			put_quote_error(info, quote);
		if (term_ctrl(info->trm_ptr, &next, 1) < 0)
			ctrl_d(info);
		if (!(info->line = mini_strjoin(info->line, next, "\n")))
			ft_exit(info, NULL);
	}
}
