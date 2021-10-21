/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:40:42 by floogman          #+#    #+#             */
/*   Updated: 2020/05/02 13:06:26 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(uintmax_t nbr, char *base, int base_size)
{
	int			len;
	char		*str;
	uintmax_t	n_cpy;

	n_cpy = nbr;
	len = (nbr == 0) ? (1) : (0);
	while (nbr > 0)
		nbr = (len++) ? (nbr / base_size) : (nbr / base_size);
	if (!(str = malloc(len + 1)))
		return (NULL);
	str[len--] = '\0';
	(!n_cpy) && (str[len--] = '0');
	while (n_cpy > 0)
	{
		str[len--] = base[n_cpy % base_size];
		n_cpy /= base_size;
	}
	return (str);
}
