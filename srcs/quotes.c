/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:05:42 by aball             #+#    #+#             */
/*   Updated: 2022/11/27 08:08:22 by aball            ###   ########.fr       */
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
	char	*tmp;

	new_line = (char **)malloc(sizeof(char *) * 1);
	if (!new_line)
		return (NULL);
	i = 0;
	x = 0;
	new_line[0] = NULL;
	while (args->s[i])
	{
		tmp = NULL;
		while (is_spc_tb(args->s[i]) && args->s[i])
			i++;
		while (args->s[i] && (single_q || double_q || !is_spc_tb(args->s[i])))
		{
			if (!check_quotes(args->s[i], &single_q, &double_q) && args->s[i])
				tmp = add_char(tmp, args->s[i]);
			i++;
		}
		new_line = append_str(new_line, tmp);
		my_free(tmp);
		x++;
	}
	return (new_line);
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
		return (remove_quotes(args, 0, 0));
	return (NULL);
}
