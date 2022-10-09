/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 20:57:18 by aball             #+#    #+#             */
/*   Updated: 2022/03/02 17:43:24 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_else_if(const char *f, va_list ap, int i, int count)
{
	if (f[i] == 'c')
		count += print_putchar(va_arg(ap, int));
	else if (f[i] == 's')
		count += print_putstr(va_arg(ap, char *));
	else if (f[i] == 'i' || f[i] == 'd')
		count += print_putnbr(va_arg(ap, int));
	else if (f[i] == 'u')
		count += ft_putnbr_uns(va_arg(ap, unsigned int));
	else if (f[i] == 'x')
		count += put_hex(va_arg(ap, unsigned int));
	else if (f[i] == 'X')
		count += put_hex_up(va_arg(ap, unsigned int));
	else if (f[i] == 'p')
		count += ft_putaddress(va_arg(ap, unsigned long long));
	return (count);
}

int	ft_printf(const char *f, ...)
{
	va_list	ap;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(ap, f);
	while (f[i])
	{
		if (f[i] == '%' && f[i + 1] != '%')
		{
			i++;
			count = ft_else_if(f, ap, i, count);
		}
		else if (f[i] == '%' && f[i + 1] == '%')
		{
			i++;
			count += print_putchar('%');
		}
		else
			count += print_putchar(f[i]);
		i++;
	}
	va_end(ap);
	return (count);
}
