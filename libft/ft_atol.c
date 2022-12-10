/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 04:06:25 by aball             #+#    #+#             */
/*   Updated: 2022/12/11 01:55:08 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	error_message(size_t *r, int s)
{
	if (*r > LLONG_MAX || (long long)*r * s < LLONG_MIN)
	{
		errno = ERANGE;
		perror("minishell: exit");
		*r = 255;
		s = 0;
		return (1);
	}
	return (0);
}

size_t	ft_atol(char *str)
{
	int			s;
	size_t		r;

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
		if (error_message(&r, s))
			return (r * s);
	}
	return (r * s);
}
