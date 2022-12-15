/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:05:42 by aball             #+#    #+#             */
/*   Updated: 2022/12/16 03:27:43 by ballzball        ###   ########.fr       */
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

void	flag_quotes(t_pipe *node, int *single_q, int *double_q)
{
	if (*single_q)
		node->single_q = 1;
	else if (*double_q)
		node->double_q = 1;
}

char	**quote_collector(t_pipe *current, int single_q, int double_q)
{
	int	i;

	i = 0;
	while (current->cmd[0][i])
	{
		if (current->cmd[0][i] == '"'
			&& check_quotes(current->cmd[0][i], &single_q, &double_q))
			current->cmd[0][i] = 1;
		if (current->cmd[0][i] == 39
			&& check_quotes(current->cmd[0][i], &single_q, &double_q))
			current->cmd[0][i] = 2;
		i++;
	}
	return (current->cmd);
}

void	remove_quotes(t_pipe **h, int single_q, int double_q)
{
	t_pipe	*current;

	current = *h;
	while (current)
	{
		current->cmd = quote_collector(current, single_q, double_q);
		current = current->next;
	}
}

char	**quote_validator(t_cmd *args, int single_q, int double_q)
{
	int	i;

	i = 0;
	while (args->s[i])
	{
		if (args->s[i] == '"' && !single_q && !double_q)
			double_q = 1;
		else if (args->s[i] == 39 && !single_q && !double_q)
			single_q = 1;
		else if (args->s[i] == '"' && !single_q && double_q)
			double_q = 0;
		else if (args->s[i] == 39 && single_q && !double_q)
			single_q = 0;
		i++;
	}
	if (!single_q && !double_q)
		return (special_split(args->s));
	return (NULL);
}
