/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:28:05 by floogman          #+#    #+#             */
/*   Updated: 2021/03/24 13:40:47 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	<command line>	::= 	<job> ';'
**							<job>
**	<job>			::=		<command> '|' <job>
**						|	<command>
**	<command>		::=		<redirection> <simple command>
**						|	<simple command>
**	<simple command>::=		<pathname> <token list>
**	<token list>	::=		<token> <token list>
**						|	(EMPTY)
*/

int		get_redirection(t_info *info, int type, char **fd, char **filename)
{
	if (info->curtok->type == type && info->curtok->next
		&& info->curtok->next->type == type)
	{
		if (tree_check_type(info, type, fd) != 0)
			return (FAILURE);
	}
	if (tree_check_type(info, type, NULL) != 0)
	{
		if (fd && *fd)
			free(*fd);
		return (FAILURE);
	}
	if (tree_check_type(info, -1, filename) != 0)
	{
		if (fd && *fd)
			free(*fd);
		if (filename)
			ft_putendl_fd("minishell: ambiguous redirect", STDERR);
		info->ret = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

t_node	*get_result(int type, char *fd, char *filename)
{
	t_node	*result;

	if (!(result = malloc(sizeof(t_node))))
		return (NULL);
	if (type == '<')
		type = REDIRECT_IN;
	else if (type == '>')
		type = REDIRECT_OUT;
	else if (type == '>' + 1)
		type = REDIRECT_APPEND;
	if (fd)
		type++;
	tree_set_params(result, type, ft_atoi(fd), filename);
	free(fd);
	return (result);
}

t_node	*redirection(t_info *info, t_node *save, char *fd, char *filename)
{
	t_node	*simplecmd_node;
	t_node	*redirection_node;
	t_node	*result;
	int		type;

	simplecmd_node = NULL;
	redirection_node = NULL;
	type = info->curtok->type;
	if (get_redirection(info, type, &fd, &filename) != 0)
		return (NULL);
	if (!(result = get_result(type, fd, filename)))
		return (tree_abort(NULL, NULL, fd, filename));
	while (info->curtok && info->curtok->type == -1)
		info->curtok = info->curtok->next;
	if (info->curtok && is_redir(info->curtok->type))
	{
		if (!(redirection_node = redirection(info, save, NULL, NULL)))
			return (tree_abort(result, NULL, fd, filename));
	}
	else
		tree_add_branch(result, redirection_node, (simplecmd_node = save));
	if (!simplecmd_node)
		tree_add_branch(result, NULL, redirection_node);
	return (result);
}

t_node	*simplecmd(t_info *info)
{
	t_node	*toklst_node;
	t_node	*result;
	char	*pathname;

	toklst_node = NULL;
	if (info->curtok)
		info->nextok = info->curtok->next;
	if (tree_check_type(info, -1, &pathname) != 0)
		return (NULL);
	if (info->curtok && info->curtok->type < 1)
		toklst_node = tokenlist(info);
	else if (info->curtok && is_redir(info->curtok->type))
	{
		while (info->curtok && is_redir(info->curtok->type))
			if (get_redirection(info, info->curtok->type, NULL, NULL) != 0)
				return (tree_abort(NULL, toklst_node, NULL, pathname));
		if (info->curtok && info->curtok->type < 1)
			toklst_node = tokenlist(info);
	}
	if (!(result = malloc(sizeof(t_node))))
		return (tree_abort(NULL, toklst_node, NULL, pathname));
	tree_set_params(result, CMDPATH, 0, pathname);
	tree_add_branch(result, NULL, toklst_node);
	return (result);
}

t_node	*tokenlist(t_info *info)
{
	t_node	*toklst_node;
	t_node	*result;
	char	*arg;

	toklst_node = NULL;
	if (info->curtok)
		info->nextok = info->curtok->next;
	if (tree_check_type(info, -1, &arg) != 0)
		return (NULL);
	if (info->curtok && info->curtok->type < 1)
		toklst_node = tokenlist(info);
	else if (info->curtok && is_redir(info->curtok->type))
	{
		while (info->curtok && is_redir(info->curtok->type))
			if (get_redirection(info, info->curtok->type, NULL, NULL) != 0)
				return (tree_abort(NULL, toklst_node, NULL, arg));
		if (info->curtok && info->curtok->type < 1)
			toklst_node = tokenlist(info);
	}
	if (!(result = malloc(sizeof(t_node))))
		return (tree_abort(NULL, toklst_node, NULL, arg));
	tree_set_params(result, ARGUMENT, 0, arg);
	tree_add_branch(result, NULL, toklst_node);
	return (result);
}
