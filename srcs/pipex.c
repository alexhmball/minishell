/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 00:34:50 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/11/30 01:55:30 by talsaiaa         ###   ########.fr       */
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
	t_pipe	*cmd;
	int		prev_pipe;
	int		child;
	int		fd[2];
	int		prev_out;

	temp = *args->pipe;
	prev_out = 0;
	prev_pipe = STDIN_FILENO;
	while (temp)
	{
		if (pipe(fd) == -1 && args->pipe_n)
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
			cmd = temp;
			temp = setting_up_ins(temp, &prev_pipe, args);
			temp = setting_up_outs(temp, args, fd, &prev_out);
			execve(cmd->path, cmd->cmd, args->env_for_excecute);
			perror(ft_strjoin("minishell: ", temp->cmd[0]));
			exit(EXIT_FAILURE);
		}
		close(prev_pipe);
		close(fd[1]);
		prev_pipe = fd[0];
		temp = temp->next;
		while (temp && temp->in)
			temp = temp->next;
		while (temp && temp->out)
		{
			temp = temp->next;
			prev_out = 1;
		}
	}
	waitpid(-1, &child, 0);
	if (args->pipe_n)
	{
		close(fd[0]);
		close(fd[1]);
	}
}
