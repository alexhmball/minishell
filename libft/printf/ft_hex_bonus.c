/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 23:22:12 by aball             #+#    #+#             */
/*   Updated: 2022/03/02 17:44:20 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	convert_hex(unsigned int n)
{
	if (n > 9)
		print_putchar(n + 87);
	else
		print_putnbr(n);
	return (1);
}

int	put_hex(unsigned int n)
{
	static int	i;

	i = 0;
	if (n > 15)
		put_hex(n / 16);
	i += convert_hex(n % 16);
	return (i);
}
