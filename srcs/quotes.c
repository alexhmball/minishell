/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:05:42 by aball             #+#    #+#             */
/*   Updated: 2022/11/29 23:46:34 by aball            ###   ########.fr       */
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

void	remove_quotes(t_pipe **head, int single_q, int double_q)
{
	int		i;
	int		flag;
	char	*tmp;
	t_pipe	*current;

	i = 0;
	flag = 0;
	current = *head;
	while (current)
	{
		tmp = NULL;
		while (current->cmd[0][i] && (single_q || double_q || !is_spc_tb(current->cmd[0][i])))
		{
			if (current->cmd[0][i] && !check_quotes(current->cmd[0][i], &single_q, &double_q))
				tmp = add_char(tmp, current->cmd[0][i]);
			if (!is_q(current->cmd[0][i]) && !flag)
			{
				flag_quotes(current, &single_q, &double_q);
				flag = 1;
			}
			i++;
		}
		i = 0;
		flag = 0;
		current->cmd = remove_str(current->cmd, 0);
		current->cmd = append_str(current->cmd, tmp);
		my_free(tmp);
		current = current->next;
	}
}

void	flag_expansion(t_cmd *args, int single_q, int i, int *x)
{
	if (args->s[i] == '$' && !is_spc_tb(args->s[i + 1])
		&& args->s[i + 1])
	{
		if (!single_q)
			args->expand[*x] = 1;
		else
			args->expand[*x] = 0;
		args->need_exp = 1;
		*x += 1;
	}
	if (args->s[i] == '|')
		args->pipe_n++;
	if (args->s[i] == '>' || args->s[i] == '<')
		args->redirect++;
}

char	**quote_validator(t_cmd *args, int single_q, int double_q)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	args->need_exp = 0;
	args->pipe_n = 0;
	args->redirect = 0;
	while (args->s[i])
	{
		flag_expansion(args, single_q, i, &x);
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
