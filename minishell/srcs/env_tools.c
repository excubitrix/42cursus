/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:15:15 by floogman          #+#    #+#             */
/*   Updated: 2021/03/26 14:33:54 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Expands the environment list with the arg passed. In the case of SHLVL being
** assigned an empty value, add_envar() (re)initializes it with 1 instead.
*/

int		add_envar(t_info *info, char *arg)
{
	char	**tmp;

	if (!(ft_strcmp(arg, "SHLVL=")))
		if (reset_shlvl(info, -1, 0) != 0)
			return (-1);
	if (!(tmp = tab_add(info->envp, arg)))
		return (-1);
	info->envp = tmp;
	return (SUCCESS);
}

/*
** Used by ft_export() to change the values of or add entries to the list of
** environment variables contained in info->envp.
*/

int		set_envar(t_info *info, char *arg, char *ptr, int append)
{
	char	*needle;
	char	*tmp;
	int		i;

	if (!(needle = ft_strndup(arg, ptr - arg)))
		return (-1);
	i = tab_stristr(info->envp, needle);
	free(needle);
	if (i != -1)
	{
		if (!append)
			if (!(tmp = ft_strdup(arg)))
				return (-1);
		if (append)
			if (!(tmp = ft_strjoin(info->envp[i], ptr)))
				return (-1);
		free(info->envp[i]);
		info->envp[i] = tmp;
	}
	else if (add_envar(info, arg) != 0)
		return (-1);
	return (SUCCESS);
}

/*
** Searches the list of environment variables for a match and returns its index
** or -1 if no match was found.
*/

int		get_envp(t_info *info, char *needle)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(needle);
	while (info->envp[i])
	{
		if (!(ft_strncmp(info->envp[i], needle, len)))
			if (!info->envp[i][len] || info->envp[i][len] == '=')
				return (i);
		i++;
	}
	return (-1);
}
