/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:02:57 by floogman          #+#    #+#             */
/*   Updated: 2021/03/26 11:15:30 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Increments the shell level by one.
*/

void		increment_num(t_info *info, int j, int key_len, int val_len)
{
	while (val_len--)
	{
		if (info->envp[j][key_len + val_len] == '9')
			info->envp[j][key_len + val_len] = '0';
		else
		{
			info->envp[j][key_len + val_len]++;
			break ;
		}
	}
}

/*
** Makes the jump from 9 to 10, 99 to 100, ect.
*/

void		increment_len(t_info *info, int j, int key_len)
{
	char	*tmp;
	int		len;

	len = 1;
	info->envp[j][key_len + len - 1] = '1';
	while (info->envp[j][key_len + len])
	{
		info->envp[j][key_len + len] = '0';
		len++;
	}
	if (!(tmp = ft_strjoin(info->envp[j], "0")))
		ft_exit(info, NULL);
	free(info->envp[j]);
	info->envp[j] = tmp;
}

/*
** Resets SHLVL to 1 if its entry in the list of environment variables is not
** present or invalid.
*/

int			reset_shlvl(t_info *info, int j, int key_len)
{
	char	**temp;
	char	*tmp;

	if (j < 0)
	{
		if (!(tmp = ft_strdup("SHLVL=1")))
			return (FAILURE);
		if (!(temp = tab_add_free(info->envp, tmp)))
			return (FAILURE);
		info->envp = temp;
	}
	else
	{
		info->envp[j][key_len] = '1';
		info->envp[j][key_len + 1] = '\0';
	}
	return (SUCCESS);
}

/*
** Entry point for incrementing the shell level.
*/

void		increment_shlvl(t_info *info, int j, int key_len)
{
	int		val_len;
	int		len;

	if (j < 0 || !str_is(&info->envp[j][key_len], &ft_isdigit))
	{
		if ((reset_shlvl(info, j, key_len)) != 0)
			ft_exit(info, NULL);
		return ;
	}
	if (!(val_len = ft_strlen(&info->envp[j][key_len])))
		return ;
	len = 0;
	while (info->envp[j][key_len + len] == '9')
		len++;
	if (len < val_len)
		increment_num(info, j, key_len, val_len);
	else
		increment_len(info, j, key_len);
}
