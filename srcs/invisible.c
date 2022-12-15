/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invisible.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 03:09:04 by ballzball         #+#    #+#             */
/*   Updated: 2022/12/16 03:18:53 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_invisible_quotes(char c, int *single_q, int *double_q)
{
	if (c == 1 && !*single_q && !*double_q)
	{
		*double_q = 1;
		return (1);
	}
	else if (c == 2 && !*single_q && !*double_q)
	{
		*single_q = 1;
		return (1);
	}
	else if (c == 1 && !*single_q && *double_q)
	{
		*double_q = 0;
		return (1);
	}
	else if (c == 2 && *single_q && !*double_q)
	{
		*single_q = 0;
		return (1);
	}
	return (0);
}

void	strip_tease(t_pipe *node, t_cmd *args)
{
	size_t	i;
	char	**temp;

	i = 0;
	while (*node->cmd && node->cmd[0][i])
	{
		if (node->cmd[0][i] == 1 || node->cmd[0][i] == 2)
			shuffle_it(node->cmd[0], i);
		else
			i++;
	}
	if (node->expand)
	{
		temp = ft_split(node->cmd[0], ' ');
		freedom(node->cmd);
		node->cmd = temp;
	}
	validate_path(node->cmd[0], args);
	if (args->path && !node->path)
		node->path = ft_strdup(args->path);
	my_free(args->path);
}
