/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 09:31:18 by floogman          #+#    #+#             */
/*   Updated: 2020/05/02 13:09:20 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len_itoa(int nb)
{
	int	len;

	len = 2;
	if (nb < 0)
		len++;
	while (nb /= 10)
		len++;
	return (len);
}

char		*ft_itoa(int n)
{
	long	tmpn;
	int		len;
	char	*str;

	tmpn = n;
	len = get_len_itoa(n);
	if (!(str = malloc(len)))
		return (NULL);
	if (tmpn < 0)
	{
		str[0] = '-';
		tmpn = -tmpn;
	}
	str[--len] = '\0';
	if (tmpn == 0)
		str[--len] = '0';
	while (len-- && tmpn)
	{
		str[len] = (tmpn % 10) + 48;
		tmpn = tmpn / 10;
	}
	return (str);
}
