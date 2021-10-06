/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 19:37:25 by floogman          #+#    #+#             */
/*   Updated: 2021/01/18 11:03:58 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "bmp.h"

int		main(int argc, char **argv)
{
	t_data	s;
	int		bmp;

	init_s(&s);
	bmp = check_input(&s, argc, argv);
	parse_scene(&s, argv[1], 0);
	is_valid(&s);
	bmp ? save_img_to_bmp(&s) : init_game(&s, 0);
	mlx_hook(s.win.ptr, 2, 1L << 0, ft_kpress, &s);
	mlx_hook(s.win.ptr, 3, 1L << 1, ft_krelease, &s);
	mlx_hook(s.win.ptr, 17, 1L << 17, ft_exit, &s);
	mlx_loop_hook(s.mlx, render_frame, &s);
	mlx_loop(s.mlx);
	return (0);
}
