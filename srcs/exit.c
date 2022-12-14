/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:16:28 by aball             #+#    #+#             */
/*   Updated: 2022/12/14 23:40:43 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pipe_size(t_pipe **head)
{
	t_pipe	*node;
	int		i;

	i = 0;
	node = *head;
	while (node)
	{
		node = node->next;
		i++;
	}
	return (i);
}

void	exit_shell(t_cmd *args, t_pipe *node)
{
	int	i;

	i = 0;
	if (pipe_size(args->pipe) == 1 && !args->flag)
		printf("exit\n");
	if (two_d_strlen(node->cmd) > 1)
	{
		while (node->cmd[1][i])
		{
			if (!ft_isdigit(node->cmd[1][i]) && node->cmd[1][0] != '-')
			{
				ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
				*args->err = 255;
				lstclear_pipe(args->pipe, my_free);
				total_freedom(args);
				exit(*args->err);
			}
			i++;
		}
		*args->err = ft_atol(node->cmd[1]);
	}
	lstclear_pipe(args->pipe, my_free);
	total_freedom(args);
	exit(*args->err);
}
