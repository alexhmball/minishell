/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 00:34:50 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/10 21:35:28 by aball            ###   ########.fr       */
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
	int		prev_pipe;
	int		child;
	int		fd[2];
	int		prev_in;
	int		prev_out;

	temp = *args->pipe;
	prev_pipe = STDIN_FILENO;
	prev_in = 0;
	prev_out = 0;
	while (temp)
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
			if (temp && temp->here_doc)
			{
				if (prev_pipe != STDIN_FILENO)
					dup2(STDIN_FILENO, prev_pipe);
				ms_heredoc(temp, fd);
			}
			if (temp && temp->in)
			{
				temp = setting_up_ins(temp, fd);
				prev_in = 1;
			}
			if (prev_pipe != STDIN_FILENO && !prev_in)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			if (temp && temp->out)
			{
				temp = setting_up_outs(temp);
				prev_out = 1;
			}
			if (!prev_out && args->pipe_n >= 1)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			if (temp && !temp->in && !temp->out && !temp->here_doc)
			{
				if (is_us(temp))
				{
					excecute_us(args, temp);
					lstclear_pipe(args->pipe, my_free);
					total_freedom(args);
					exit(EXIT_SUCCESS);
				}
				else
					execute_them(args, temp);
			}
		}
		wait(&child);
		close(fd[1]);
		prev_pipe = fd[0];
		while (temp && temp->next && temp->in)
			temp = temp->next;
		while (temp && temp->next && temp->out)
			temp = temp->next;
		if (temp && temp->next && temp->here_doc)
			args->pipe_n++;
		if (temp && !temp->in && !temp->out)
			temp = temp->next;
		if (args->pipe_n > 0)
			args->pipe_n--;
	}
	wait(&child);
	close(fd[0]);
	close(fd[1]);
}
