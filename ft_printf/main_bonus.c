/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:32:52 by floogman          #+#    #+#             */
/*   Updated: 2021/10/05 08:39:38 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include <stdio.h>

int		main(void)
{
	int ret;
	double i = 0.00;
	while (i <= 10)
	{
		int prec = 0;
		while (prec < 8)
		{
			if (i > 9)
				ret = ft_printf("-%.*g", prec, i);
			else
				ret = ft_printf("-%.*g", prec, i);
			ft_printf("|\t\tret:%d\n", ret);
			prec += 1;
		}
		i += 0.9999999;
	}
	ft_printf("*****************************\n");
	ret = ft_printf("%-5c", 'c');
	ft_printf("|\t\tret:%d\n", ret);
	ft_printf("*****************************\n");
	ret = ft_printf("%20.17f%20f%20.2f%20.f%20f%20.10f", 1.025978548534310421, 0.0894255, -3.85, -78952.4568789, -65268.0, -56.47852012685);
	ft_printf("|\t\tret:%d\n", ret);
	ft_printf("*****************************\n");
	ret = ft_printf("%20.17g%20g%20g%20g%20.2g%20.g", 1.025978548534310421, 1119875.36428, 1.5, -78952.1568789, -65268.0, -68.62879452382636);
	ft_printf("|\t\tret:%d\n", ret);
	ft_printf("*****************************\n");
	ret = ft_printf("%20e%20e%20e%20e%20e%20e", 5.111, 9875.36428, 1.5, -78952.1568789, -65268.0, -68.62879452382636);
	ft_printf("|\t\tret:%d\n", ret);
	ft_printf("*****************************\n");
	ret = ft_printf("%20e", 0.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001);
	ft_printf("|\t\tret:%d\n", ret);
	ft_printf("*****************************\n");
	int x = 0;
	int *p = &x;
	ret = ft_printf("%20c %20s %20d %20i %20e %20f %20lu %20x %20s %20p", 'c', "Hello", -321234, 15, -78952.1568789, -65268.0, -9875786572382636, 6788254, "World", &p);
	ft_printf("|\t\tret:%d\n", ret);
	ft_printf("*****************************\n");
	int n1 = 0;
	int n2 = 0;
	ret = ft_printf("%20c %n %20g %20s %20c %n %20u %20lx", '.', &n1, 69878.6543, "!", 'c', &n2, 12457, 7890655400);
	ft_printf("|\t\tret:%d\n", ret);
	ft_printf("n1:%d\tn2:%d\n", n1, n2);
	ft_printf("*****************************\n");
	return (0);
}
