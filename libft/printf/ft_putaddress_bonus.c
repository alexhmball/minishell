/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 23:25:08 by aball             #+#    #+#             */
/*   Updated: 2022/03/02 17:46:41 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	hex_write(unsigned long long n)
{
	if (n > 9)
		print_putchar(n + 87);
	else
		print_putnbr(n);
	return (1);
}

static int	hexer(unsigned long long n)
{
	static int	i;

	i = 0;
	if (n > 15)
		hexer(n / 16);
	i += hex_write(n % 16);
	return (i);
}

int	ft_putaddress(unsigned long long ptr)
{
	int	c;

	c = print_putstr("0x");
	c += hexer((unsigned long long)ptr);
	return (c);
}
