/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 00:34:50 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/11/25 20:41:38 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	my_lst_size(t_pipe *temp)
{
	size_t	i;

	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	pipex(t_cmd *args)
{
	t_pipe	*temp;
	t_pipe	*last;
	int		prev_pipe;
	int		child;
	int		fd[2];
	int		infile;
	int		outfile;
	size_t	lst_size;
	size_t	i;

	temp = *args->pipe;
	lst_size = my_lst_size(temp);
	last = lstlast_pipe(temp);
	i = 0;
	if (last->out)
		lst_size--;
	prev_pipe = STDIN_FILENO;
	if (temp->in)
	{
		lst_size--;
		infile = open(temp->path, O_RDONLY);
		temp->next->in = 1;
		temp = temp->next;
	}
	while (i <= lst_size - 2 && args->pipe_n)
	{
		printf("n: %d\n", args->pipe_n);
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
			if (prev_pipe == STDIN_FILENO && temp->in)
			{
				dup2(infile, STDIN_FILENO);
				prev_pipe = infile;
				close(infile);
			}
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			execve(temp->path, temp->cmd, args->env_for_excecute);
			perror(ft_strjoin("minishell: ", temp->cmd[0]));
			exit(EXIT_FAILURE);
		}
		close(prev_pipe);
		close(fd[1]);
		prev_pipe = fd[0];
		temp = temp->next;
		i++;
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
		else if (prev_pipe == STDIN_FILENO && infile && !args->pipe_n)
		{
			dup2(infile, STDIN_FILENO);
			close(infile);
		}
		if (last->out)
		{
			outfile = open(last->cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0777);
			dup2(outfile, STDOUT_FILENO);
			close(outfile);
		}
		if (!temp->path)
		{
			args->err = 127;
			printf("minishell: %s: command not found\n", args->cmd[0]);
		}
		execve(temp->path, temp->cmd, args->env_for_excecute);
		// perror(ft_strjoin("minishell: ", temp->cmd[0]));
	}
	wait(&child);
	if (args->pipe_n)
	{
		close(fd[0]);
		close(fd[1]);
	}
	exit(EXIT_SUCCESS);
}