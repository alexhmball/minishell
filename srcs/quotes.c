/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:05:42 by aball             #+#    #+#             */
/*   Updated: 2022/12/08 20:09:20 by aball            ###   ########.fr       */
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

char	*quote_collector(t_pipe *current, char *tmp, int single_q, int double_q)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (current->cmd[0][i]
			&& (single_q || double_q || !is_spc_tb(current->cmd[0][i])))
	{
		if (current->cmd[0][i]
			&& !check_quotes(current->cmd[0][i], &single_q, &double_q))
			tmp = add_char(tmp, current->cmd[0][i]);
		if (!is_q(current->cmd[0][i]) && !flag && (single_q || double_q))
		{
			flag_quotes(current, &single_q, &double_q);
			flag = 1;
		}
		i++;
	}
	return (tmp);
}

void	remove_quotes(t_pipe **head, int single_q, int double_q, t_cmd *args)
{
	char	*tmp;
	t_pipe	*current;

	current = *head;
	while (current)
	{
		tmp = NULL;
		find_expansion(current, single_q, double_q, args);
		tmp = quote_collector(current, tmp, single_q, double_q);
		current->cmd = remove_str(current->cmd, 0);
		current->cmd = append_str(current->cmd, tmp);
		my_free(tmp);
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
