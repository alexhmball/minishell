/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 00:34:50 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/11 03:25:54 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_pipe_exec(t_pipe *temp, t_cmd *args)
{
	if (temp && !temp->in && !temp->out && !temp->here_doc)
	{
		if (is_us(temp))
		{
			excecute_us(args, temp);
			lstclear_pipe(args->pipe, my_free);
			total_freedom(args);
			close(args->fd[0]);
			close(args->fd[1]);
			exit(EXIT_SUCCESS);
		}
		else
			execute_them(args, temp);
	}
}

t_pipe	*ms_proc_ins_outs(t_pipe *temp, t_cmd *args, int prev_pipe, int pre_out)
{
	args->prev_in = 0;
	if (temp && temp->in)
	{
		temp = setting_up_ins(temp, args);
		args->prev_in = 1;
	}
	if (prev_pipe != STDIN_FILENO && !args->prev_in)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	if (temp && temp->out)
	{
		temp = setting_up_outs(temp, args);
		pre_out = 1;
	}
	if (!pre_out && args->pipe_n >= 1)
	{
		dup2(args->fd[1], STDOUT_FILENO);
		close(args->fd[1]);
	}
	if (prev_pipe == STDIN_FILENO)
		close(args->fd[0]);
	return (temp);
}

void	children(t_pipe *temp, pid_t child, int prev_pipe, t_cmd *args)
{
	int	prev_out;

	prev_out = 0;
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
			ms_heredoc(temp, args);
		}
		temp = ms_proc_ins_outs(temp, args, prev_pipe, prev_out);
		ms_pipe_exec(temp, args);
		lstclear_pipe(args->pipe, my_free);
	}
	wait(NULL);
}

t_pipe	*parent_catching_up(t_pipe *temp, t_cmd *args)
{
	while (temp && temp->next && (temp->in || temp->out))
		temp = temp->next;
	if (temp && temp->next && temp->here_doc)
		args->pipe_n++;
	if (temp && !temp->in && !temp->out)
		temp = temp->next;
	if (args->pipe_n > 0)
		args->pipe_n--;
	return (temp);
}


void	pipex(t_cmd *args)
{
	t_pipe	*temp;
	pid_t	child;
	int		prev_pipe;

	temp = *args->pipe;
	prev_pipe = STDIN_FILENO;
	signal(SIGINT, handle_this);
	while (temp)
	{
		if (pipe(args->fd) == -1)
		{
			perror("pipe: ");
			exit(EXIT_FAILURE);
		}
		child = fork();
		children(temp, child, prev_pipe, args);
		wait(&child);
		close(args->fd[1]);
		prev_pipe = args->fd[0];
		temp = parent_catching_up(temp, args);
	}
	wait(&child);
	close(args->fd[0]);
	close(args->fd[1]);
}
