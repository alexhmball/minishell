/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 20:57:28 by aball             #+#    #+#             */
/*   Updated: 2022/03/02 17:43:59 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

int		ft_printf(const char *f, ...);
int		print_putstr(char *str);
int		print_putchar(char c);
int		print_putnbr(int n);
int		ft_putnbr_uns(unsigned int n);
int		print_strlen(char *str);
int		put_hex_up(unsigned int n);
int		put_hex(unsigned int n);
int		ft_putaddress(unsigned long long ptr);

#endif
