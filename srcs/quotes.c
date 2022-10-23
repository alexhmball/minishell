/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:05:42 by aball             #+#    #+#             */
/*   Updated: 2022/10/23 20:06:04 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quotes(char c, int *single_q, int *double_q)
{
	if (c == '"' && !*single_q && !*double_q)
	{
		*double_q = 1;
		return (1);
	}
	else if (c == 39 && !*single_q && !*double_q)
	{
		*single_q = 1;
		return (1);
	}
	else if (c == '"' && !*single_q && *double_q)
	{
		*double_q = 0;
		return (1);
	}
	else if (c == 39 && *single_q && !*double_q)
	{
		*single_q = 0;
		return (1);
	}
	return (0);
}

char	*remove_quotes(char *line, int remove, int single_q, int double_q)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = (char *)malloc(sizeof(char) * ((ft_strlen(line) - remove) + 1));
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		while (check_quotes(line[i], &single_q, &double_q))
			i++;
		new_line[j] = line[i];
		i++;
		j++;
	}
	new_line[i] = 0;
	return (new_line);
}

char	*quote_validator(char *line, int single_q, int double_q)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (line[i])
	{
		if (line[i] == '"' && !single_q && !double_q)
			double_q = 1;
		else if (line[i] == 39 && !single_q && !double_q)
			single_q = 1;
		else if (line[i] == '"' && !single_q && double_q)
		{
				double_q = 0;
				counter += 2;
		}
		else if (line[i] == 39 && single_q && !double_q)
		{
			single_q = 0;
			counter += 2;
		}
		i++;
	}
	if (!single_q && !double_q)
		return (remove_quotes(line, counter, 0, 0));
	return (NULL);
}