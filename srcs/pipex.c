/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 00:34:50 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/09 05:27:54 by talsaiaa         ###   ########.fr       */
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
	int		prev_out;

	temp = *args->pipe;
	prev_out = 0;
	prev_pipe = 0;
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
			// ft_putstr_fd(temp->cmd[0], 2);
			if (temp->here_doc)
			{
				ms_heredoc(temp, fd);
				temp = temp->next;
			}
			if (temp->in)
			{
				setting_up_ins(temp, &prev_pipe,fd);
				temp = temp->next;
			}
			if (temp->out)
			{
				setting_up_outs(temp, args, fd, &prev_out);
				temp = temp->next;
			}
			if (!temp->in && !temp->out && !temp->here_doc)
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
		wait(&child);
		close(fd[1]);
		prev_pipe = fd[0];
		// if (temp->next)
		temp = temp->next;
		while (temp && temp->next && temp->next->in)
			temp = temp->next;
		while (temp && temp->next && temp->next->out)
			temp = temp->next;
		while (temp && !temp->in && !temp->out)
			temp = temp->next;
		// while (temp && temp->here_doc)
		// 	temp = temp->next;
		// while (temp && temp->in)
		// 	temp = temp->next;
		// while (temp && temp->out)
		// {
		// 	temp = temp->next;
		// 	prev_out = 1;
		// }
	}
	wait(&child);
	close(fd[0]);
	close(fd[1]);
}
