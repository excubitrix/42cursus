/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:22:22 by floogman          #+#    #+#             */
/*   Updated: 2021/03/26 16:37:39 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Formates the command and its arguments.
*/

int		prep_cmd(t_info *info, t_cmd *cmd, t_node *job, t_node *arg)
{
	int		i;

	i = 0;
	if (!job || job->type != CMDPATH)
		return (FAILURE);
	while (arg && (arg->type == ARGUMENT || arg->type == CMDPATH))
	{
		arg = arg->right;
		i++;
	}
	if (!(cmd->argv = malloc(sizeof(char *) * (i + 1))))
		ft_exit(info, NULL);
	arg = job;
	i = 0;
	while (arg && (arg->type == ARGUMENT || arg->type == CMDPATH))
	{
		if (!(cmd->argv[i] = ft_strdup(arg->data)))
			ft_exit(info, cmd);
		arg = arg->right;
		i++;
	}
	cmd->argv[i] = NULL;
	cmd->argc = i;
	return (SUCCESS);
}

/*
** Execute_cmd() sends the command to the correct function to further
** handle the command. In a series of pipes, only the first of the
** build up commands is granted passage.
*/

void	execute_cmd(t_info *info, t_node *job)
{
	t_cmd	cmd;
	int		i;

	if (!info->charge)
		return ;
	if (prep_cmd(info, &cmd, job, job) != 0)
		return ;
	i = -1;
	while (++i < 7)
	{
		if (ft_strcmp(cmd.argv[0], info->cmdstr[i]) == 0)
		{
			info->ret = (*info->cmdexe[i])(info, &cmd);
			break ;
		}
	}
	if (i == 7)
		info->ret = binexe(info, &cmd, NULL, NULL);
	clear_cmd(&cmd);
	ft_close(info->pipe_in);
	ft_close(info->pipe_out);
	info->charge = 0;
}

/*
** If the command is of type PIPE a child process is created to
** carry out the command. The child inherits the file descriptors
** and their redirections of the parent.
*/

int		pipe_cmd(t_info *info, pid_t pid, int *fd)
{
	pipe(fd);
	if (!(pid = fork()))
	{
		ft_close(fd[1]);
		dup2(fd[0], STDIN);
		info->pipe_in = fd[0];
		info->parent = 0;
		info->error = 0;
		return (2);
	}
	else if (pid < 0)
	{
		info->ret = FAILURE;
		return (ft_exit(info, NULL));
	}
	else
	{
		ft_close(fd[0]);
		dup2(fd[1], STDOUT);
		info->pipe_out = fd[1];
		info->last = 0;
		return (1);
	}
}

/*
** If the command is of a redirection type, fds are set accordingly.
** After, we move to the next node.
*/

void	redirect_cmd(t_info *info, t_node **cmd)
{
	info->fd = (*cmd)->fd;
	if ((*cmd)->type == REDIRECT_IN || (*cmd)->type == REDIRECT_FD_IN)
		open_file_in(info, (*cmd)->data);
	else if ((*cmd)->type == REDIRECT_OUT || (*cmd)->type == REDIRECT_FD_OUT)
		open_file_out(info, (*cmd)->data, 0);
	else if ((*cmd)->type == REDIRECT_APPEND
		|| (*cmd)->type == REDIRECT_FD_APPEND)
		open_file_out(info, (*cmd)->data, 1);
	*cmd = (*cmd)->right;
}

/*
** Entry point for the execution of the commad tree.
*/

void	execute(t_info *info, t_node *cmd, int prev)
{
	pid_t	pid;
	int		pipe;
	int		fd[2];

	pid = 0;
	if (!cmd)
		return ;
	while (cmd && cmd->type >= REDIRECT_IN && cmd->type <= REDIRECT_FD_APPEND)
		redirect_cmd(info, &cmd);
	pipe = 0;
	if (cmd->type == PIPE || prev == PIPE)
		pipe = pipe_cmd(info, pid, fd);
	if (cmd->type != CMDPATH && pipe != 1)
		execute(info, cmd->right, cmd->type);
	if (cmd->type == PIPE)
		cmd = cmd->left;
	if (pipe != 1 && !info->error)
		execute_cmd(info, cmd);
}
