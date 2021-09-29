/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 09:31:18 by floogman          #+#    #+#             */
/*   Updated: 2021/09/28 12:16:53 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	unsigned long long	result;
	char				sign;

	result = 0;
	sign = '+';
	while ((*nptr > 8 && *nptr < 14) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		sign = *nptr++;
	while (ft_isdigit(*nptr))
		result = result * 10 + (*nptr++ - 48);
	if (result > LONG_MAX)
	{
		if (sign == '-')
			return (0);
		return (-1);
	}
	if (sign == '-')
		return (-result);
	return (result);
}
