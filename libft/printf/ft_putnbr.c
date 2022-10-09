/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 03:40:37 by aball             #+#    #+#             */
/*   Updated: 2022/03/02 17:48:09 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_n(int n)
{
	int	c;

	c = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		c++;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		c++;
	}
	return (c);
}

int	print_putnbr(int n)
{
	int		c;

	c = count_n(n);
	if (n == -2147483648)
	{
		print_putnbr(n / 10);
		print_putchar('8');
	}
	else if (n < 0)
	{
		print_putchar('-');
		print_putnbr(-n);
	}
	else
	{
		if (n > 9)
			print_putnbr(n / 10);
		print_putchar(48 + n % 10);
	}
	return (c);
}
