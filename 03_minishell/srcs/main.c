/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 08:21:34 by floogman          #+#    #+#             */
/*   Updated: 2021/10/22 12:25:41 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig		g_sig;

/*
** Resets and frees variables that need freeing/resetting before another command
** can be executed. It also catches the exit statuses of piped commands.
*/

static int	free_and_reset(t_info *info)
{
	int		status;

	free(info->cmd);
	info->cmd = NULL;
	clear_toklst(info);
	clear_tree(info);
	restore_std(info);
	close_fds(info);
	reset_fds(info);
	wait(&status);
	status = WEXITSTATUS(status);
	info->ret = (!info->last) ? status : info->ret;
	if (!info->parent)
	{
		free_all(info, NULL, -1);
		exit(info->ret);
	}
	info->error = 0;
	if ((info->and && info->ret) || (info->or && !info->ret))
		return (1);
	return (0);
}

/*
** Parses the input and executes it command by command.
*/

void		parse_and_exec(t_info *info, int skip)
{
	char	*cmd;

	while (*info->line && *info->line != '#')
	{
		info->charge = 1;
		info->parent = 1;
		info->last = 1;
		info->and = 0;
		info->or = 0;
		cmd = get_cmd(info, info->line, NULL, NULL);
		if (!skip)
		{
			info->size = ft_strlen(info->cmd) + 1;
			build_toklst(info, cmd);
			info->curtok = info->toklst;
			info->pretok = info->curtok;
			if (info->curtok)
				info->nextok = info->curtok->next;
			info->tree = build_tree(info);
			execute(info, info->tree, -1);
			tab_delone(info->envp, "_=");
		}
		skip = free_and_reset(info);
	}
}

/*
** This is where minishell asks for input and passes it on to parse_and_exec if
** everything checks out.
*/

void		minishell(t_info *info, int not_pipe, int i)
{
	while (1)
	{
		init_sig();
		get_cmdline(info, not_pipe);
		i = check_syntax(info->line, 1, 0, 0);
		if (i < 0 || (info->line[i] && info->line[i] != '#'))
		{
			ft_putstr_fd("minishell: syntax error near ", STDERR);
			ft_putstr_fd("unexpected token `", STDERR);
			if (info->line[i] == '\n')
				ft_putstr_fd("newline", STDERR);
			else
			{
				ft_putchar_fd(info->line[i], STDERR);
				if (info->line[i] == info->line[i + 1])
					ft_putchar_fd(info->line[i], STDERR);
			}
			ft_putendl_fd("'", STDERR);
			info->ret = SYNTAX_ERR;
		}
		else
			parse_and_exec(info, 0);
		free(info->line);
		info->line = NULL;
	}
}

/*
** Makes some changes to the list of environment variables.
*/

void		setup_env(t_info *info, char *arg)
{
	char	**tmp;
	int		i;

	if (tab_stristr(info->envp, "_=") < 0)
		set__(info, NULL, arg);
	if ((i = get_envp(info, "OLDPWD")) >= 0)
		info->envp[i][7] = '\0';
	else
	{
		if (!(tmp = tab_add(info->envp, "OLDPWD")))
			ft_exit(info, NULL);
		info->envp = tmp;
	}
	increment_shlvl(info, tab_stristr(info->envp, "SHLVL="),
		ft_strlen("SHLVL="));
}

/*
** Initializes all the nesseccary variables.
*/

int			main(int argc, char **argv, char **envp)
{
	t_info	info;
	t_term	trm;
	int		not_pipe;

	(void)argc;
	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	init_info(&info, envp);
	info.trm_ptr = &trm;
	trm.initialised = 0;
	not_pipe = ft_isatty(STDIN);
	if (not_pipe)
		if (!init_term(&trm, get_value(&info, "TERM=")))
			ft_exit(&info, NULL);
	if (get_path(&info, NULL) != 0
		|| !(info.home = ft_strdup(get_value(&info, "HOME="))))
		ft_exit(&info, NULL);
	setup_env(&info, argv[0]);
	minishell(&info, not_pipe, 0);
	return (SUCCESS);
}
