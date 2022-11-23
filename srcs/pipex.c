/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 00:34:50 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/11/23 23:34:35 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pipex(t_cmd *args)
{
	t_pipe	*temp;
	int		prev_pipe;
	int		child;
	int		fd[2];

	temp = *args->pipe;
	prev_pipe = STDIN_FILENO;
	while (temp->next)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe: ");
			exit(EXIT_FAILURE);
		}
		child = fork();
		if (child == -1)
		{
			perror("fork: ");
			exit(EXIT_FAILURE);
		}
		if (!child)
		{
			if (prev_pipe != STDIN_FILENO)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			execve(temp->path, temp->cmd, args->env_for_excecute);
			perror("exec: ");
			exit(EXIT_FAILURE);
		}
		close(prev_pipe);
		close(fd[1]);
		prev_pipe = fd[0];
		temp = temp->next;
	}
	child = fork();
	if (child == -1)
	{
		perror("fork: ");
		exit(EXIT_FAILURE);
	}
	if (!child)
	{
		if (prev_pipe != STDIN_FILENO && args->pipe_n)
		{
			dup2(prev_pipe, STDIN_FILENO);
			close(prev_pipe);
		}
		execve(temp->path, temp->cmd, args->env_for_excecute);
	}
	wait(&child);
	if (args->pipe_n)
	{
		close(fd[0]);
		close(fd[1]);
	}
	exit(EXIT_SUCCESS);
}