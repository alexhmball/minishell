/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:35:15 by aball             #+#    #+#             */
/*   Updated: 2022/11/24 15:21:30 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_spc_tb(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	count_dollar(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '$')
			counter++;
		i++;
	}
	return (counter);
}

int	is_q(char c)
{
	if (c == '"' || c == 39)
		return (1);
	return (0);
}

int	string_count(char *line)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (line[i])
	{
		while (is_spc_tb(line[i]) && line[i])
			i++;
		while (!is_spc_tb(line[i]) && line[i])
			i++;
		counter++;
		if (!line[i])
			break ;
		i++;
	}
	return (counter);
}
