/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 20:12:46 by aball             #+#    #+#             */
/*   Updated: 2022/03/02 17:45:55 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	plus_flag(const char *f, va_list ap, t_var *var)
{
	int	a;

	while (f[var->i] == '+')
		var->i++;
	if (f[var->i] == 'd' || f[var->i] == 'i')
	{
		a = va_arg(ap, int);
		if (a >= 0)
			var->count += print_putchar('+');
		var->count += print_putnbr(a);
	}
}

static void	hash_flag(const char *f, va_list ap, t_var *var)
{
	int	a;

	var->i++;
	if (f[var->i] == 'x')
	{
		a = va_arg(ap, unsigned int);
		if (a != 0)
			var->count += print_putstr("0x");
		var->count += put_hex(a);
	}
	else if (f[var->i] == 'X')
	{
		a = va_arg(ap, unsigned int);
		if (a != 0)
			var->count += print_putstr("0X");
		var->count += put_hex_up(a);
	}
}

static void	space_flag(const char *f, va_list ap, t_var *var)
{
	int	a;

	while (f[var->i] == ' ')
		var->i++;
	if (f[var->i] == 'd' || f[var->i] == 'i')
	{
		a = va_arg(ap, int);
		if (a >= 0)
			var->count += print_putchar(' ');
		var->count += print_putnbr(a);
	}
}

static int	ft_else_if(const char *f, va_list ap, t_var *var)
{
	if (f[var->i] == '+')
		plus_flag(f, ap, var);
	else if (f[var->i] == '#')
		hash_flag(f, ap, var);
	else if (f[var->i] == ' ')
		space_flag(f, ap, var);
	else if (f[var->i] == 'c')
		var->count += print_putchar(va_arg(ap, int));
	else if (f[var->i] == 's')
		var->count += print_putstr(va_arg(ap, char *));
	else if (f[var->i] == 'i' || f[var->i] == 'd')
		var->count += print_putnbr(va_arg(ap, int));
	else if (f[var->i] == 'u')
		var->count += ft_putnbr_uns(va_arg(ap, unsigned int));
	else if (f[var->i] == 'x')
		var->count += put_hex(va_arg(ap, unsigned int));
	else if (f[var->i] == 'X')
		var->count += put_hex_up(va_arg(ap, unsigned int));
	else if (f[var->i] == 'p')
		var->count += ft_putaddress(va_arg(ap, unsigned long long));
	return (var->count);
}

int	ft_printf(const char *f, ...)
{
	va_list	ap;
	t_var	var;

	var.i = 0;
	var.count = 0;
	va_start(ap, f);
	while (f[var.i])
	{
		if (f[var.i] == '%' && f[var.i + 1] != '%')
		{
			var.i++;
			ft_else_if(f, ap, &var);
		}
		else if (f[var.i] == '%' && f[var.i + 1] == '%')
		{
			var.i++;
			var.count += print_putchar('%');
		}
		else
			var.count += print_putchar(f[var.i]);
		var.i++;
	}
	va_end(ap);
	return (var.count);
}
