/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_norm_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 03:32:12 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/16 03:43:57 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ms_parent_norm(t_cmd *args, t_pipe *temp, int prev_pipe)
{
	int	free;

	if (temp->here_doc)
		wait(NULL);
	close(args->fd[1]);
	free = prev_pipe;
	prev_pipe = args->fd[0];
	if (free != STDIN_FILENO && prev_pipe != STDIN_FILENO)
		close(free);
	return (prev_pipe);
}

void	ms_child_norm(t_cmd *args, int prev_pipe, int pre_out)
{
	if (!pre_out && args->pipe_n >= 1)
	{
		dup2(args->fd[1], STDOUT_FILENO);
		close(args->fd[1]);
	}
	if (!pre_out && args->pipe_n < 1)
	{
		close(args->fd[1]);
		close(args->fd[0]);
		if (prev_pipe != STDIN_FILENO)
			close(prev_pipe);
	}
	close(args->fd[0]);
}
