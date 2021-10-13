/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 12:03:05 by floogman          #+#    #+#             */
/*   Updated: 2021/03/09 09:53:08 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check_base(char *base)
{
	int i;
	int j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+'
		|| base[i] < 33 || base[i] > 127)
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[j] == base[i])
				return (0);
			j++;
		}
		i++;
	}
	return (i);
}

static int	get_index(char c, char *base)
{
	int i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int			ft_atoi_base_c(char *str, char *base)
{
	int nbr;
	int sign;
	int base_index;
	int base_len;

	if (!str || !base || (base_len = check_base(base)) < 2)
		return (0);
	while (*str && (*str == '\t' || *str == '\v' || *str == '\n'
			|| *str == '\r' || *str == '\f' || *str == ' '))
		str++;
	sign = 1;
	while (*str && (*str == '-' || *str == '+'))
	{
		sign *= (*str == '-') ? -1 : 1;
		str++;
	}
	nbr = 0;
	while (*str && (base_index = get_index(*str, base)) != -1)
	{
		nbr = (nbr * base_len) + base_index;
		str++;
	}
	return (nbr * sign);
}
