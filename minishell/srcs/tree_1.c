/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:22:23 by floogman          #+#    #+#             */
/*   Updated: 2021/03/24 18:41:00 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	<command line>	::= 	<job> ';'
**							<job> '&&'
**							<job>
**	<job>			::=		<command> '|' <job>
**						|	<command>
**	<command>		::=		<redirection> <simple command>
**						|	<simple command>
**	<simple command>::=		<pathname> <token list>
**	<token list>	::=		<token> <token list>
**						|	(EMPTY)
*/

t_node	*build_tree(t_info *info)
{
	t_node	*result;

	while (info->nextok && info->nextok->type != ';' &&
		info->nextok->type != '&' && info->nextok->type != '&' + 1
		&& info->nextok->type != '|' + 1)
		info->nextok = info->nextok->next;
	if (info->nextok && (info->nextok->type == ';' ||
		info->nextok->type == '&' || info->nextok->type == '&' + 1
		|| info->nextok->type == '|' + 1))
	{
		if (!(result = job(info)))
			return (NULL);
		if (tree_check_type(info, ';', NULL) != 0
			&& tree_check_type(info, '&', NULL) != 0
			&& tree_check_type(info, '&' + 1, NULL) != 0
			&& tree_check_type(info, '|' + 1, NULL) != 0)
			return (tree_abort(NULL, result, NULL, NULL));
		return (result);
	}
	return (job(info));
}

t_node	*job(t_info *info)
{
	if (info->curtok)
		info->nextok = info->curtok->next;
	while (info->nextok && info->nextok->type != '|')
	{
		info->pretok = info->nextok;
		info->nextok = info->nextok->next;
	}
	if (info->nextok && info->nextok->type == '|')
		return (job1(info));
	return (cmd(info));
}

t_node	*job1(t_info *info)
{
	t_node	*cmd_node;
	t_node	*job_node;
	t_node	*result;

	if (!(cmd_node = cmd(info)))
		return (NULL);
	if (tree_check_type(info, '|', NULL) != 0)
		return (tree_abort(NULL, cmd_node, NULL, NULL));
	if (!(job_node = job(info)))
		return (tree_abort(NULL, cmd_node, NULL, NULL));
	if (!(result = malloc(sizeof(t_node))))
		return (tree_abort(cmd_node, job_node, NULL, NULL));
	tree_set_params(result, PIPE, 0, NULL);
	tree_add_branch(result, cmd_node, job_node);
	return (result);
}

t_node	*cmd(t_info *info)
{
	t_node	*simplecmd_node;
	t_node	*redirection_node;
	t_tok	*save;

	save = info->curtok;
	while (info->curtok && is_redir(info->curtok->type))
		if (get_redirection(info, info->curtok->type, NULL, NULL) != 0)
			return (NULL);
	if (!(simplecmd_node = simplecmd(info)))
		return (NULL);
	info->curtok = save;
	while (info->curtok && info->curtok->type == -1)
		info->curtok = info->curtok->next;
	if (info->curtok && is_redir(info->curtok->type))
	{
		if (!(redirection_node = redirection(info, simplecmd_node, NULL, NULL)))
			return (tree_abort(NULL, simplecmd_node, NULL, NULL));
		return (redirection_node);
	}
	return (simplecmd_node);
}
