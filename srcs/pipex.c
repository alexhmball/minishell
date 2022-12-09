/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 00:34:50 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/09 22:51:34 by talsaiaa         ###   ########.fr       */
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

	temp = *args->pipe;
	prev_pipe = STDIN_FILENO;
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
			ft_putstr_fd("loop\n", 2);
			if (temp && temp->here_doc)
				ms_heredoc(temp, fd, args);
			if (temp && temp->in)
				temp = setting_up_ins(temp);
			else if (prev_pipe != STDIN_FILENO)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			if (temp && temp->out)
				temp = setting_up_outs(temp);
			else if (args->pipe_n || args->heredoc_n)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			if (temp && !temp->in && !temp->out && !temp->here_doc)
			{
				if (is_us(temp))
				{
					excecute_us(args, temp);
					total_freedom(args);
					lstclear_pipe(args->pipe, my_free);
					exit(EXIT_SUCCESS);
				}
				else
					execute_them(args, temp);
			}
		}
		ft_putstr_fd("loop out\n", 2);
		wait(&child);
		close(fd[1]);
		prev_pipe = fd[0];
		while (temp && temp->next && temp->in)
			temp = temp->next;
		while (temp && temp->next && temp->out)
			temp = temp->next;
		while (temp && !temp->in && !temp->out && !temp->here_doc)
			temp = temp->next;
		while (temp && temp->next && temp->here_doc)
		{
			args->heredoc_n--;
			temp = temp->next;
		}
	}
	wait(&child);
	close(fd[0]);
	close(fd[1]);
}
