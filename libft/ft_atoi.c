/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:33:49 by aball             #+#    #+#             */
/*   Updated: 2022/08/31 20:59:41 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	error_message(long r, int s)
{
	if (r > INT_MAX || r * s < INT_MIN)
	{
		write(2, "Error\n", 6);
	}
}

//function that converts a string to an integer
int	ft_atoi(const char *str)
{
	int		s;
	long	r;

	r = 0;
	s = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			s *= -1;
		str++;
		break ;
	}
	while (*str >= '0' && *str <= '9')
	{
		r *= 10;
		r += *str - '0';
		str++;
		error_message(r, s);
	}
	return (r * s);
}
