/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:16:28 by aball             #+#    #+#             */
/*   Updated: 2022/12/08 19:21:07 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_shell(t_cmd *args, t_pipe *node)
{
	int	i;

	i = 0;
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
