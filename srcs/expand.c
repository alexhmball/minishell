/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:58:39 by aball             #+#    #+#             */
/*   Updated: 2022/12/12 03:04:02 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	find_expand(t_pipe *current, int single_q, int double_q, t_cmd *args)
{
	int	dollar;
	int	i;

	i = 0;
	dollar = locate_dollar(current->cmd[0]);
	if (dollar != -1)
	{
		while (current->cmd[0][i] && current->cmd[0][i] != '$')
			check_quotes(current->cmd[0][i++], &single_q, &double_q);
		flag_quotes(current, &single_q, &double_q);
		expand_dollar(current, args);
	}
}

void	insert_expansion(t_pipe *node, char *expand, t_cmd *args, int dollar)
{
	char	*env;
	char	*new_line;
	int		i;
	size_t	len;

	env = my_getenv(expand, args);
	if (!env)
		env = (char *)ft_calloc(1, sizeof(char));
	len = (ft_strlen(env) + ft_strlen(node->cmd[0]) + 1) - ft_strlen(expand);
	new_line = (char *)malloc(sizeof(char) * len);
	i = -1;
	while (++i < dollar - 1 && node->cmd[0][i])
		new_line[i] = node->cmd[0][i];
	dollar = i + ft_strlen(expand) + 1;
	len = 0;
	while (env[len])
		new_line[i++] = env[len++];
	while (node->cmd[0][dollar])
		new_line[i++] = node->cmd[0][dollar++];
	new_line[i] = 0;
	node->cmd = remove_str(node->cmd, 0);
	node->cmd = append_str(node->cmd, new_line);
	my_free(env);
	my_free(new_line);
}

void	sub_it(int i, int dollar, t_pipe *node, t_cmd *args)
{
	char	*tmp;

	tmp = ft_substr(node->cmd[0], dollar, i - dollar);
	insert_expansion(node, tmp, args, dollar);
	my_free(tmp);
}

int	check_need(int i, t_pipe *node, t_cmd *args)
{
	int		dollar;

	dollar = i;
	while (node->cmd[0][i] && node->cmd[0][i] != 39
			&& node->cmd[0][i] != '"')
		i++;
	if (node->cmd[0][dollar + 1] == '?' || node->cmd[0][dollar + 1] == '$')
	{
		if (node->cmd[0][dollar + 1] == '$')
			node->cmd[0] = insert_pid(node->cmd[0], args);
		else
			node->cmd[0] = insert_error(node->cmd[0], args);
		return (1);
	}
	else
	{
		dollar++;
		if (i - dollar > 0)
		{
			sub_it(i, dollar, node, args);
			return (1);
		}
	}
	return (0);
}

void	expand_dollar(t_pipe *node, t_cmd *args)
{
	int		i;
	int		single_q;
	int		double_q;

	i = 0;
	single_q = 0;
	double_q = 0;
	while (*node->cmd && node->cmd && node->cmd[0][i])
	{
		check_quotes(node->cmd[0][i], &single_q, &double_q);
		if (node->cmd[0][i] == '$' && !single_q)
		{
			if (check_need(i, node, args))
				return ;
		}
		i++;
	}
}
