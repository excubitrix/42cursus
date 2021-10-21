/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 08:09:02 by floogman          #+#    #+#             */
/*   Updated: 2021/03/26 09:36:41 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Initializes g_sig.
*/

void	init_sig(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exstat = 0;
}

/*
** Initializes an array of strings each matching a build-in.
*/

void	init_cmdstr(t_info *info)
{
	info->cmdstr[0] = "echo";
	info->cmdstr[1] = "cd";
	info->cmdstr[2] = "pwd";
	info->cmdstr[3] = "export";
	info->cmdstr[4] = "unset";
	info->cmdstr[5] = "env";
	info->cmdstr[6] = "exit";
}

/*
** Initializes an array of function pointers each pointing to a build-in
** function which name is stored in cmdstr at the same index.
*/

void	init_cmdexe(t_info *info)
{
	info->cmdexe[0] = &ft_echo;
	info->cmdexe[1] = &ft_cd;
	info->cmdexe[2] = &ft_pwd;
	info->cmdexe[3] = &ft_export;
	info->cmdexe[4] = &ft_unset;
	info->cmdexe[5] = &ft_env;
	info->cmdexe[6] = &ft_exit;
}

/*
** Initializes our main struct.
*/

int		init_info(t_info *info, char **envp)
{
	info->in = dup(STDIN);
	info->out = dup(STDOUT);
	info->path = NULL;
	info->line = NULL;
	info->cmd = NULL;
	info->toklst = NULL;
	info->tree = NULL;
	info->cmdstr = NULL;
	info->cmdexe = NULL;
	reset_fds(info);
	if (!(info->envp = tab_dup(envp))
		|| !(info->cmdstr = malloc(sizeof(char *) * 7))
		|| !(info->cmdexe = malloc(sizeof(int (*)(t_info *, t_cmd *)) * 7)))
		ft_exit(info, NULL);
	init_cmdstr(info);
	init_cmdexe(info);
	info->error = 0;
	info->and = 0;
	info->or = 0;
	info->ret = SUCCESS;
	return (SUCCESS);
}

/*
** Initializes a new token.
*/

t_tok	*init_tok(t_tok *tok, int size)
{
	if (!(tok->data = malloc((size + 1))))
		return (NULL);
	tok->data[0] = '\0';
	tok->type = 0;
	tok->digit = 1;
	tok->space = 0;
	tok->next = NULL;
	return (tok);
}
