/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:16:28 by aball             #+#    #+#             */
/*   Updated: 2022/12/09 20:59:22 by codespace        ###   ########.fr       */
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
	if (pipe_size(args->pipe) == 1)
		printf("exit\n");
	if (two_d_strlen(node->cmd) > 1)
	{
		while (node->cmd[1][i])
		{
			if (!ft_isdigit(node->cmd[1][i]) && node->cmd[1][0] != '-')
			{
				errno = EINVAL;
				perror("minishell: exit");
				*args->err = 255;
				total_freedom(args);
				lstclear_pipe(args->pipe, my_free);
				exit(*args->err);
			}
			i++;
		}
		*args->err = ft_atol(node->cmd[1]);
	}
	total_freedom(args);
	lstclear_pipe(args->pipe, my_free);
	exit(*args->err);
}
