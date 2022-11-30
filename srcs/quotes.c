/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:05:42 by aball             #+#    #+#             */
/*   Updated: 2022/12/01 00:37:09 by aball            ###   ########.fr       */
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

void	insert_expansion(t_pipe *node, char *expand, t_cmd *args)
{
	char	*env;
	char	*new_line;
	int		i;
	int		save;
	int		j;
	size_t	len;

	env = my_getenv(expand, args);
	if (!env)
		env = (char *)ft_calloc(1, sizeof(char));
	len = ft_strlen(env) + ft_strlen(node->cmd[0]) + 1;
	len -= ft_strlen(expand);
	new_line = (char *)malloc(sizeof(char) * len);
	i = 0;
	while (node->cmd[0][i] && node->cmd[0][i] != '$')
	{
		new_line[i] = node->cmd[0][i];
		i++;
	}
	save = i;
	save += ft_strlen(expand) + 1;
	j = 0;
	while (env[j])
		new_line[i++] = env[j++];
	while (node->cmd[0][save])
		new_line[i++] = node->cmd[0][save++];
	new_line[i] = 0;
	node->cmd = remove_str(node->cmd, 0);
	node->cmd = append_str(node->cmd, new_line);
}

void	expand_dollar(t_pipe *node, t_cmd *args)
{
	int		i;
	int		dollar;
	int		single_q;
	int		double_q;
	char	*tmp;

	i = 0;
	single_q = 0;
	double_q = 0;
	dollar = locate_dollar(node->cmd[0]);
	while (node->cmd[0][i])
	{
		check_quotes(node->cmd[0][i], &single_q, &double_q);
		if (node->cmd[0][i] == '$' && !single_q)
		{
			while (node->cmd[0][i] && node->cmd[0][i] != 39 && node->cmd[0][i] != '"')
				i++;
			if (node->cmd[0][dollar + 1] == '?')
				node->cmd[0] = insert_error(node->cmd[0], args);
			else
			{
				dollar++;
				tmp = ft_substr(node->cmd[0], dollar, i - dollar);
				insert_expansion(node, tmp, args);
			}
		}
		i++;
	}
}

void	remove_quotes(t_pipe **head, int single_q, int double_q, t_cmd *args)
{
	int		i;
	int		flag;
	char	*tmp;
	int		dollar;
	t_pipe	*current;

	i = 0;
	flag = 0;
	current = *head;
	while (current)
	{
		tmp = NULL;
		dollar = locate_dollar(current->cmd[0]);
		if (dollar != -1)
		{
			while (current->cmd[0][i] && current->cmd[0][i] != '$')
			{
				check_quotes(current->cmd[0][i], &single_q, &double_q);
				i++;
			}
			flag_quotes(current, &single_q, &double_q);
			expand_dollar(current, args);
			i = 0;
			single_q = 0;
			double_q = 0;
		}
		while (current->cmd[0][i] && (single_q || double_q || !is_spc_tb(current->cmd[0][i])))
		{
			if (current->cmd[0][i] && !check_quotes(current->cmd[0][i], &single_q, &double_q))
				tmp = add_char(tmp, current->cmd[0][i]);
			if (!is_q(current->cmd[0][i]) && !flag && (single_q || double_q))
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
		validate_path(current->cmd[0], args);
		if (args->path)
			current->path = ft_strdup(args->path);
		my_free(tmp);
		current = current->next;
	}
}

void	flag_expansion(t_cmd *args, int i)
{
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
	args->pipe_n = 0;
	args->redirect = 0;
	while (args->s[i])
	{
		flag_expansion(args, i);
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
