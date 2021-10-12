/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimchr_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 07:02:43 by floogman          #+#    #+#             */
/*   Updated: 2020/08/20 06:53:22 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrimchr_back(char *s, char c)
{
	int		len;

	len = ft_strlen(s);
	while (s[--len] != c)
		s[len] = '\0';
	s[len] = '\0';
	return (s);
}
