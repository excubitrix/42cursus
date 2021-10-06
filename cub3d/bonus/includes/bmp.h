/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:35:09 by floogman          #+#    #+#             */
/*   Updated: 2020/10/25 10:35:14 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

void	write_pixels(t_data *s, int fd);
void	ft_itoc(unsigned char *start, int value);
void	write_header(t_data *s, int fd, int size);
void	save_img_to_bmp(t_data *s);

#endif
