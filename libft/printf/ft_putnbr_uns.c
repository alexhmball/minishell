/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_uns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 03:36:56 by aball             #+#    #+#             */
/*   Updated: 2022/03/02 17:47:40 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_n(unsigned int n)
{
	int	c;

	c = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		c++;
	}
	return (c);
}

int	ft_putnbr_uns(unsigned int n)
{
	int	c;

	c = count_n(n);
	if (n > 9)
		print_putnbr(n / 10);
	print_putchar(48 + n % 10);
	return (c);
}
