/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:03:05 by floogman          #+#    #+#             */
/*   Updated: 2020/03/21 17:12:04 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_format(t_tab *tab, int len)
{
	char *format;

	format = NULL;
	if (len <= 0)
		return (1);
	if (!(format = ft_substr(tab->f, (tab->i - len), len)))
		return (0);
	ft_putstr_fd(format, 1);
	free(format);
	tab->len += len;
	return (1);
}

static int	parser(t_tab *tab)
{
	int counter;

	counter = 0;
	if (ft_strcmp(tab->f, "%") == 0)
		return (1);
	while (tab->f[tab->i])
	{
		if (tab->f[tab->i] == '%')
		{
			if (!(print_format(tab, counter)))
				return (0);
			reinit_tab(tab);
			if (!(dispatcher(tab)))
				return (0);
			counter = 0;
		}
		else
			counter++;
		tab->i++;
	}
	if (!(print_format(tab, counter)))
		return (0);
	return (1);
}

int			ft_printf(const char *format, ...)
{
	t_tab	*tab;
	int		len;

	if (!(tab = (t_tab *)malloc(sizeof(t_tab) * 1)))
		return (-1);
	tab->f = format;
	tab = init_tab(tab);
	if (format)
	{
		va_start(tab->ap, format);
		if (!(parser(tab)))
		{
			va_end(tab->ap);
			free(tab);
			return (-1);
		}
		va_end(tab->ap);
	}
	len = tab->len;
	free(tab);
	return (len);
}
