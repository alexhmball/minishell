/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 00:34:50 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/05 15:07:54 by codespace        ###   ########.fr       */
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
	char	*here_doc;
	int		here_doc_len;
	int		typed_len;

	temp = *args->pipe;
	prev_out = 0;
	prev_pipe = 0;
	here_doc_len = 0;
	typed_len = 0;
	while (temp && temp->here_doc)
	{
		here_doc_len = ft_strlen(temp->cmd[0]);
		here_doc = readline("> ");
		typed_len = ft_strlen(here_doc);
		while (1)
		{
			if (!ft_strncmp(here_doc, temp->cmd[0], here_doc_len) && here_doc_len == typed_len)
				break ;
			here_doc = readline("> ");
			typed_len = ft_strlen(here_doc);
		}
		temp = temp->next;
	}
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
			if (!temp->in && !temp->out)
				cmd = temp;
			else
				cmd = NULL;
			setting_up_ins(temp, &prev_pipe, args);
			setting_up_outs(temp, args, fd, &prev_out);
			if (cmd != NULL)
			{
				if (is_us(cmd))
				{
					excecute_us(args, cmd);
					total_freedom(args);
					lstclear_pipe(args->pipe, my_free);
					exit(EXIT_SUCCESS);
				}
				else
					execute_them(args, cmd);
				// execve(cmd->path, cmd->cmd, args->env_for_excecute);
				// perror(ft_strjoin("minishell: ", cmd->cmd[0]));
				// exit(EXIT_FAILURE);
			}
		}
		// close(prev_pipe);
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
	while (waitpid(-1, &child, 0) > 0)
		;
	if (args->pipe_n)
	{
		close(fd[0]);
		close(fd[1]);
	}
}
