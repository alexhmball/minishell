/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 00:34:50 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/11/29 20:34:02 by talsaiaa         ###   ########.fr       */
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
	// t_pipe	*last;
	t_pipe	*cmd;
	int		prev_pipe;
	int		child;
	int		fd[2];
	// int		infile;
	// int		outfile;
	// int		prev_node;
	int		prev_out;
	// size_t	lst_size;
	// size_t	i;

	temp = *args->pipe;
	// prev_node = 0;
	prev_out = 0;
	// lst_size = my_lst_size(temp);
	// printf("size: %zu\n", lst_size);
	// last = lstlast_pipe(temp);
	// i = 0;
	// if (last->out)
	// 	lst_size--;
	prev_pipe = STDIN_FILENO;
	// while (temp->in && temp->next)
	// {
	// 	// lst_size--;
	// 	infile = open(temp->path, O_RDONLY);
	// 	if (infile < 0)
	// 	{
	// 		perror(ft_strjoin("minishell: ", temp->cmd[0]));
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	// temp->next->in = 1;
	// 	prev_node = 1;
	// 	temp = temp->next;
	// }
	while (temp)
	{
		printf("n: %d\n", args->pipe_n);
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
			// if (temp->out)
			// 	temp = temp->next;
			cmd = temp;
			printf("cmd: %s\n", temp->cmd[0]);
			// printf("cmd next: %d\n", temp->next->out);
			temp = setting_up_ins(temp, &prev_pipe);
			// if (temp->next)
			// 	temp = temp->next;
			printf("hello\n");
			// temp = temp->next;
			temp = setting_up_outs(temp, args, fd, &prev_out);
			printf("temp after: %s\n", temp->cmd[0]);
			// if (prev_pipe != STDIN_FILENO && !temp->in)
			// {
			// 	dup2(prev_pipe, STDIN_FILENO);
			// 	close(prev_pipe);
			// }
			// while (prev_pipe != STDIN_FILENO && temp->in)
			// {
			// 	infile = open(temp->path, O_RDONLY);
			// 	if (infile < 0)
			// 	{
			// 		perror(ft_strjoin("minishell: ", temp->cmd[0]));
			// 		exit(EXIT_FAILURE);
			// 	}
			// 	close(infile);
			// 	prev_pipe = infile;
			// 	temp = temp->next;
			// }
			// if (prev_pipe == STDIN_FILENO && prev_node)
			// {
			// 	dup2(infile, STDIN_FILENO);
			// 	prev_pipe = infile;
			// 	close(infile);
			// }
			// if (prev_pipe == infile && temp->in)
			// {
			// 	dup2(prev_pipe, STDIN_FILENO);
			// 	close(prev_pipe);
			// 	cmd = temp;
			// }
			// while (temp->next && temp->next->out)
			// {
			// 	outfile = open(temp->next->cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0666);
			// 	// if (!temp->next)
			// 	// 	dup2(outfile, STDOUT_FILENO);
			// 	close(outfile);
			// 	temp = temp->next;
			// }
			// if (temp->out)
			// {
			// 	outfile = open(temp->cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0666);
			// 	dup2(outfile, STDOUT_FILENO);
			// 	close(outfile);
			// 	prev_out = 1;
			// }
			// if (temp->next && args->pipe_n && !prev_out)
			// {
			// 	dup2(fd[1], STDOUT_FILENO);
			// 	close(fd[1]);
			// }
			execve(cmd->path, cmd->cmd, args->env_for_excecute);
			perror(ft_strjoin("minishell: ", temp->cmd[0]));
			exit(EXIT_FAILURE);
		}
		close(prev_pipe);
		close(fd[1]);
		prev_pipe = fd[0];
		// while (temp->next && temp->next->out)
		// 	temp = temp->next;
		while (temp && temp->in)
			temp = temp->next;
		while (temp && temp->out)
			temp = temp->next;
		temp = temp->next;
		// i++;
	}
	// child = fork();
	// if (child == -1)
	// {
	// 	perror("fork: ");
	// 	exit(EXIT_FAILURE);
	// }
	// if (!child)
	// {
	// 	if (prev_pipe != STDIN_FILENO && args->pipe_n)
	// 	{
	// 		dup2(prev_pipe, STDIN_FILENO);
	// 		close(prev_pipe);
	// 	}
	// 	else if (prev_pipe == STDIN_FILENO && infile && !args->pipe_n)
	// 	{
	// 		dup2(infile, STDIN_FILENO);
	// 		close(infile);
	// 	}
	// 	if (last->out)
	// 	{
	// 		outfile = open(last->cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0777);
	// 		dup2(outfile, STDOUT_FILENO);
	// 		close(outfile);
	// 	}
	// 	if (!temp->path)
	// 	{
	// 		args->err = 127;
	// 		printf("minishell: %s: command not found\n", temp->cmd[0]);
	// 	}
	// 	execve(temp->path, temp->cmd, args->env_for_excecute);
	// 	// perror(ft_strjoin("minishell: ", temp->cmd[0]));
	// }
	waitpid(-1, &child, 0);
	// wait(&child);
	if (args->pipe_n)
	{
		close(fd[0]);
		close(fd[1]);
	}
	// exit(EXIT_SUCCESS);
}