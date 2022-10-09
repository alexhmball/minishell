/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 20:26:11 by aball             #+#    #+#             */
/*   Updated: 2022/03/02 17:46:16 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_var
{
	int		i;
	int		count;
}			t_var;

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
