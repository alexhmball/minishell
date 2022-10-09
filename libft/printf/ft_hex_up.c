/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_up.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 03:42:37 by aball             #+#    #+#             */
/*   Updated: 2022/03/02 17:44:41 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	convert_hex_up(unsigned int n)
{
	if (n > 9)
		print_putchar(n + 55);
	else
		print_putnbr(n);
	return (1);
}

int	put_hex_up(unsigned int n)
{
	static int	i;

	i = 0;
	if (n > 15)
		put_hex_up(n / 16);
	i += convert_hex_up(n % 16);
	return (i);
}
