/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 00:34:50 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/16 02:56:24 by ballzball        ###   ########.fr       */
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
	// wait(NULL);
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
	int		free;

	temp = *args->pipe;
	prev_pipe = STDIN_FILENO;
	signal(SIGINT, handle_this);
	while (temp)
	{
		// if (temp->next)
		// {
		if (pipe(args->fd) == -1)
			ms_error_messages(args, temp, -420);
		// }
		// ft_putstr_fd("args->fd[0]: ", 2);
		// ft_putnbr_fd(args->fd[0], 2);
		// ft_putstr_fd("\nargs->fd[1]: ", 2);
		// ft_putnbr_fd(args->fd[1], 2);
		// ft_putstr_fd("\nprev_pipe: ", 2);
		// ft_putnbr_fd(prev_pipe, 2);
		// ft_putchar_fd('\n', 2);
		if (!temp->next)
		{
			close(args->fd[1]);
		// 	// close(prev_pipe);
		}
		child = fork();
		children(temp, child, prev_pipe, args);
		if (temp->here_doc)
			wait(NULL);
		close(args->fd[1]);
		free = prev_pipe;
		prev_pipe = args->fd[0];
		if (free != STDIN_FILENO && prev_pipe != STDIN_FILENO)
			close(free);
		temp = parent_catching_up(temp, args);
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	if (prev_pipe != STDIN_FILENO)
		close(prev_pipe);
	close(args->fd[0]);
	close(args->fd[1]);
}
