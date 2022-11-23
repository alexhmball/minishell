/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 00:34:50 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/11/23 03:05:06 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pipex(t_cmd *args)
{
	t_pipe	*temp;
	int		prev_pipe;
	int		child;
	int		fd[2];
	int		my_stdin;
	int		my_stdout;

	temp = *args->pipe;
	my_stdin = dup(STDIN_FILENO);
	my_stdout = dup(STDOUT_FILENO);
	prev_pipe = my_stdin;
	while (temp->next)
	{
		pipe(fd);
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
			if (prev_pipe != my_stdin)
			{
				dup2(prev_pipe, my_stdin);
				// close(prev_pipe);
			}
			dup2(fd[1], my_stdout);
			// close(fd[1]);
			// close(my_stdin);
			// close(STDIN_FILENO);
			close(STDOUT_FILENO);
			execve(temp->path, temp->cmd, args->env_for_excecute);
			perror("exec: ");
			exit(EXIT_FAILURE);
		}
		close(prev_pipe);
		close(fd[1]);
		wait(&child);
		// close(my_stdin);
		// dup2(prev_pipe, fd[0]);
		prev_pipe = dup(fd[0]);
		// prev_pipe = fd[0];
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
		if (prev_pipe != my_stdin)
		{
			dup2(prev_pipe, my_stdin);
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
			close(prev_pipe);
		}
		// close(my_stdout);
		execve(temp->path, temp->cmd, args->env_for_excecute);
	}
	close(fd[0]);
	close(fd[1]);
	close(prev_pipe);
	close(my_stdout);
	close(my_stdin);
	wait(&child);
	return ;
}