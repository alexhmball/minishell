/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:58:39 by aball             #+#    #+#             */
/*   Updated: 2022/12/11 10:09:15 by ballzball        ###   ########.fr       */
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

char	*insert_pid(char *line, t_cmd *args)
{
	char	*err_num;
	char	*new_line;
	int		len;
	int		i;
	int		j;

	err_num = ft_itoa(args->pid);
	len = ft_strlen(err_num) + ft_strlen(line);
	new_line = (char *)malloc(sizeof(char) * (len));
	i = 0;
	j = 0;
	while (line[i] && line[i] != '$')
	{
		new_line[i] = line[i];
		i++;
	}
	len = i + 2;
	while (err_num[j])
		new_line[i++] = err_num[j++];
	while (line[len])
		new_line[i++] = line[len++];
	my_free(line);
	my_free(err_num);
	new_line[i] = 0;
	return (new_line);
}

char	*insert_error(char *line, t_cmd *args)
{
	char	*err_num;
	char	*new_line;
	int		len;
	int		i;
	int		j;

	err_num = ft_itoa(*args->err);
	len = ft_strlen(err_num) + ft_strlen(line);
	new_line = (char *)malloc(sizeof(char) * (len));
	i = 0;
	j = 0;
	while (line[i] && line[i] != '$')
	{
		new_line[i] = line[i];
		i++;
	}
	len = i + 2;
	while (err_num[j])
		new_line[i++] = err_num[j++];
	while (line[len])
		new_line[i++] = line[len++];
	my_free(line);
	my_free(err_num);
	new_line[i] = 0;
	return (new_line);
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

int	check_need(int i, t_pipe *node, t_cmd *args)
{
	int		dollar;
	char	*tmp;

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
			tmp = ft_substr(node->cmd[0], dollar, i - dollar);
			insert_expansion(node, tmp, args, dollar);
			my_free(tmp);
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
