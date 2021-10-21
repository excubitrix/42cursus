/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 07:58:10 by floogman          #+#    #+#             */
/*   Updated: 2021/03/26 18:53:45 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Frees all elements of a linked list of type t_tok recursively, starting with
** the element pointed to by t_tok *tok when the function is first called.
*/

void	free_toks(t_tok *tok)
{
	if (tok)
	{
		free(tok->data);
		free_toks(tok->next);
		free(tok);
	}
}

/*
** Passes the first element of our token list to free_toks() if present and sets
** its pointer to NULL before returning.
*/

void	clear_toklst(t_info *info)
{
	if (!info->toklst)
		return ;
	free_toks(info->toklst);
	info->toklst = NULL;
}

/*
** Passes the first node of our command tree to tree_del_node() if present and
** sets its pointer to NULL before returning.
*/

void	clear_tree(t_info *info)
{
	if (!info->tree)
		return ;
	tree_del_node(info->tree);
	info->tree = NULL;
}

/*
** Frees all allocated variables contained in t_cmd *cmd.
*/

void	clear_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (!cmd)
		return ;
	while (i < cmd->argc)
	{
		free(cmd->argv[i]);
		cmd->argv[i] = NULL;
		i++;
	}
	free(cmd->argv);
	cmd->argc = 0;
}

/*
** Frees all allocated memory. Called before exiting.
*/

void	free_all(t_info *info, t_cmd *cmd, int i)
{
	if (info->path)
		free(info->path);
	if (info->home)
		free(info->home);
	if (info->line)
		free(info->line);
	if (info->cmd)
		free(info->cmd);
	if (info->envp)
	{
		while (info->envp[++i])
			free(info->envp[i]);
		free(info->envp);
	}
	if (info->cmdstr)
		free(info->cmdstr);
	if (info->cmdexe)
		free(info->cmdexe);
	clear_toklst(info);
	clear_tree(info);
	clear_cmd(cmd);
	if (info->trm_ptr->initialised)
		clear_term(info->trm_ptr);
}
