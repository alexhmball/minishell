/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 00:34:50 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/16 03:44:23 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_pipe_exec(t_pipe *temp, t_cmd *args)
{
	close(args->fd[0]);
	close(args->fd[1]);
	if (temp && !temp->in && !temp->out && !temp->here_doc && !temp->append)
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
	else
	{
		lstclear_pipe(args->pipe, my_free);
		total_freedom(args);
		exit(EXIT_SUCCESS);
	}
}

t_pipe	*ms_proc_ins_outs(t_pipe *temp, t_cmd *args, int prev_pipe, int pre_out)
{
	args->prev_in = 0;
	if (temp && temp->in)
	{
		temp = setting_up_ins(temp, args, prev_pipe);
		args->prev_in = 1;
	}
	if (prev_pipe != STDIN_FILENO && !args->prev_in)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
		close(args->fd[0]);
	}
	if (prev_pipe != STDIN_FILENO)
		close(prev_pipe);
	if (temp && (temp->out || temp->append))
	{
		temp = setting_up_outs(temp, args);
		close(args->fd[1]);
		pre_out = 1;
	}
	ms_child_norm(args, prev_pipe, pre_out);
	return (temp);
}

void	children(t_pipe *temp, pid_t child, int prev_pipe, t_cmd *args)
{
	int	prev_out;

	prev_out = 0;
	if (child == -1)
	{
		perror("fork: ");
		lstclear_pipe(args->pipe, my_free);
		total_freedom(args);
		exit(EXIT_FAILURE);
	}
	if (!child)
	{
		signal(SIGQUIT, sig_igor);
		if (temp && temp->here_doc)
			ms_heredoc(temp, args, prev_pipe);
		temp = ms_proc_ins_outs(temp, args, prev_pipe, prev_out);
		if (prev_pipe != STDIN_FILENO)
			close(prev_pipe);
		ms_pipe_exec(temp, args);
	}
	if (temp->here_doc)
		wait(NULL);
}

t_pipe	*parent_catching_up(t_pipe *temp, t_cmd *args)
{
	while (temp && (temp->in || temp->out || temp->append))
		temp = temp->next;
	if (temp && temp->next && temp->here_doc)
		args->pipe_n++;
	if (temp && !temp->in && !temp->out && !temp->append)
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
			ms_error_messages(args, temp, -420);
		if (!temp->next)
			close(args->fd[1]);
		child = fork();
		children(temp, child, prev_pipe, args);
		prev_pipe = ms_parent_norm(args, temp, prev_pipe);
		temp = parent_catching_up(temp, args);
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	if (prev_pipe != STDIN_FILENO)
		close(prev_pipe);
	close(args->fd[0]);
	close(args->fd[1]);
}
