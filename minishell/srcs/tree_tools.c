/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 10:25:11 by floogman          #+#    #+#             */
/*   Updated: 2021/03/24 15:48:12 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks if the type of the current token matches that of the
** type passed. If bufptr is non-NULL, it makes a dublicate of
** data and stores the pointer in bufptr.
*/

int		tree_check_type(t_info *info, int type, char **bufptr)
{
	if (!info->curtok)
		return (FAILURE);
	if (info->curtok->type == type)
	{
		if (bufptr != NULL)
			if (!(*bufptr = ft_strdup(info->curtok->data)))
				ft_exit(info, NULL);
		info->pretok = info->curtok;
		info->curtok = info->curtok->next;
		if (info->curtok && info->curtok->next)
			info->nextok = info->curtok->next;
		return (SUCCESS);
	}
	return (FAILURE);
}

/*
** Sets a tree node's parameters.
*/

void	tree_set_params(t_node *node, int type, int fd, char *data)
{
	if (node != NULL)
	{
		node->type = type;
		node->fd = fd;
		node->data = data;
	}
}

/*
** Sets a tree node's left and right pointers.
*/

void	tree_add_branch(t_node *node, t_node *left, t_node *right)
{
	if (node != NULL)
	{
		node->left = left;
		node->right = right;
	}
}

/*
** Frees all nodes of a binary tree of type t_node recursively,
** starting with the node pointed to by t_node *node when the
** function is first called.
*/

void	tree_del_node(t_node *node)
{
	if (!node)
		return ;
	if (node->data)
		free(node->data);
	tree_del_node(node->left);
	tree_del_node(node->right);
	free(node);
}

/*
** Is called upon error and frees all the memory already
** allocated for the tree.
*/

void	*tree_abort(t_node *left, t_node *right,
			void *tofree, void *freetoo)
{
	tree_del_node(left);
	tree_del_node(right);
	if (tofree)
		free(tofree);
	if (freetoo)
		free(freetoo);
	return (NULL);
}
