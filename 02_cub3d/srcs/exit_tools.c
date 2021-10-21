/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 08:24:22 by floogman          #+#    #+#             */
/*   Updated: 2021/10/07 09:12:09 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_spr(t_data *s)
{
	int		i;

	i = 0;
	if (!s->spr)
		return ;
	while (i < s->snbr)
	{
		if (s->spr[i])
			free(s->spr[i]);
		i++;
	}
	free(s->spr);
}

void	free_tex(t_data *s)
{
	int		i;

	i = 0;
	while (i < 5)
	{
		if (s->tex[i].ptr)
			free(s->tex[i].ptr);
		if (s->tex[i].addr)
			free(s->tex[i].addr);
		if (s->tex[i].path)
			free(s->tex[i].path);
		i++;
	}
}

/*
** To test for leaks, put the following line just above "exit(0);":
** system("leaks cub3D > leaks.txt");
*/

int		ft_exit(t_data *s)
{
	if (s->line)
		free(s->line);
	if (s->win.ptr)
		mlx_destroy_window(s->mlx, s->win.ptr);
	if (s->img.ptr)
		mlx_destroy_image(s->mlx, s->img.ptr);
	free_tex(s);
	if (s->map.ptr)
		free(s->map.ptr);
	free_spr(s);
	if (s->sorder)
		free(s->sorder);
	if (s->sdst)
		free(s->sdst);
	if (s->zbuffer)
		free(s->zbuffer);
	if (s->errmsg)
		free(s->errmsg);
	exit(0);
}

void	ft_abort(t_data *s, int msg, char *file, int line)
{
	if (msg)
	{
		ft_printf(RED"Error"RE"\n: %s", s->errmsg[msg - 1]);
		if (msg <= 3)
			ft_printf("line %d of .cub file", s->ln);
		else if (msg >= 15 && msg < 18)
			ft_printf("[%d:%d]", s->col, s->ln);
		else if (msg >= 14 && msg < 18)
			ft_printf("line %d near col %d of .cub file", s->ln, s->col + 1);
		ft_printf(".\n");
	}
	else
		perror(RED"Error"RE"\n");
	if (file && line)
		ft_printf(BLACK"Program exited in [%s] on line %d."RE"\n", file, line);
	ft_exit(s);
}

void	init_errmsg(t_data *s)
{
	if (!(s->errmsg = malloc(sizeof(char **) * ERRNUM)))
		ft_abort(s, 0, __FILE__, __LINE__);
	s->errmsg[0] = "Bad type identifier on ";
	s->errmsg[1] = "Duplicate element on ";
	s->errmsg[2] = "Missing parameter(s) on ";
	s->errmsg[3] = "The map is too small";
	s->errmsg[4] = "Missing map";
	s->errmsg[5] = "Player symbol was not found";
	s->errmsg[6] = "Map is not the last element";
	s->errmsg[7] = "Missing element";
	s->errmsg[8] = "Program expected an argument";
	s->errmsg[9] = "Too many arguments";
	s->errmsg[10] = "Invalid second argument";
	s->errmsg[11] = "One or more R,G,B colors are out of range";
	s->errmsg[12] = "Invalid resolution";
	s->errmsg[13] = "Unexpected character(s) on ";
	s->errmsg[14] = "Duplicate player symbol found in map at ";
	s->errmsg[15] = "Invalid character found in map at ";
	s->errmsg[16] = "Hole in wall found in map at ";
	s->errmsg[17] = "First argument is not a .cub file";
}
