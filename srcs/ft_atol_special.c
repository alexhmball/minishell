/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 05:05:01 by ballzball         #+#    #+#             */
/*   Updated: 2022/12/16 03:20:43 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_atol_special(const char *str)
{
	size_t	i;
	size_t	nbr;

	i = 0;
	nbr = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		nbr = nbr * 10 + str[i] - '0';
		if (nbr >= 1000)
		{
			ft_putstr_fd(
				"minishell: warning: shell level too high resetting to 1\n", 2);
			return (0);
		}
		i++;
	}
	return (nbr);
}
