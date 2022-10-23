/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:04:08 by aball             #+#    #+#             */
/*   Updated: 2022/10/23 22:34:36 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	skip_q(char c, int *single_q, int *double_q)
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
	else if (*single_q || *double_q)
		return (1);
	return (0);
}

static int		word_count(char *line, int single_q, int double_q)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (line[i])
	{
		while (skip_q(line[i], &single_q, &double_q))
		{
			counter++;
			i++;
		}
		if (is_spc_tb(line[i]))
			i++;
		else
			{
				counter++;
				i++;
			}
	}
	return (counter);
}

static char	**cut(char *line, char **split, int single_q, int double_q)
{
	int	i;
	int	x;
	int	start;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	x = 0;
	while (line[i])
	{
		while (is_spc_tb(line[i]) && line[i])
		{
			i++;
			start++;
			end++;
		}
		while ((skip_q(line[i], &single_q, &double_q) || !is_spc_tb(line[i])) && line[i])
		{
			i++;
			end++;
		}
		split[x++] = ft_substr(line, start, end - start);
		start = end;
	}
	return (split);
}

char	**special_split(char *cmd)
{
	char	**split;
	int		single_q;
	int		double_q;
	int		c;

	single_q = 0;
	double_q = 0;
	if (!cmd)
		return (NULL);
	c = word_count(cmd, single_q, double_q);
	split = (char **)malloc(sizeof(char *) * (c + 1));
	if (!split)
		return (NULL);
	cut(cmd, split, single_q, double_q);
	split[c] = 0;
	return (split);
}