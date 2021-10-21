/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:40:42 by floogman          #+#    #+#             */
/*   Updated: 2021/10/05 08:45:18 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_base(uintmax_t nbr, char *base, int base_size)
{
	int			len;
	char		*str;
	uintmax_t	n_cpy;

	n_cpy = nbr;
	len = 0;
	if (!nbr)
		len = 1;
	while (nbr > 0)
	{
		nbr /= base_size;
		len++;
	}
	str = malloc((len + 1) * sizeof(char));
	if (!str)
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
