/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:05:42 by aball             #+#    #+#             */
/*   Updated: 2022/11/12 01:17:59 by ballzball        ###   ########.fr       */
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

char	**remove_quotes(t_cmd *args, int single_q, int double_q)
{
	int		i;
	int		x;
	char	**new_line;

	i = string_count(args->line);
	new_line = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	x = 0;
	while (args->line[i])
	{
		new_line[x] = NULL;
		while (is_spc_tb(args->line[i]) && args->line[i])
			i++;
		while (args->line[i] && (single_q || double_q || !is_spc_tb(args->line[i])))
		{
			if (!check_quotes(args->line[i], &single_q, &double_q) && args->line[i])
				new_line[x] = add_char(new_line[x], args->line[i]);
			i++;
		}
		x++;
	}
	new_line[x] = NULL;
	return (new_line);
}

char	**quote_validator(t_cmd *args, int single_q, int double_q)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	args->need_exp = 0;
	while (args->line[i])
	{
		if (args->line[i] == '$' && !is_spc_tb(args->line[i + 1])
			&& args->line[i + 1] && !is_q(args->line[i + 1]))
			{
				if (!single_q)
					args->expand[x++] = 1;
				else
					args->expand[x++] = 0;
				args->need_exp = 1;
			}
		if (args->line[i] == '"' && !single_q && !double_q)
			double_q = 1;
		else if (args->line[i] == 39 && !single_q && !double_q)
			single_q = 1;
		else if (args->line[i] == '"' && !single_q && double_q)
				double_q = 0;
		else if (args->line[i] == 39 && single_q && !double_q)
			single_q = 0;
		i++;
	}
	if (!single_q && !double_q)
		return (remove_quotes(args, 0, 0));
	return (NULL);
}
