/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_up_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 03:52:47 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/09 05:32:09 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	setting_up_ins(t_pipe *temp, int *prev_pipe, int (*fd))
{
	int	infile;

	(void)fd;
	// if (temp->next && !temp->in && !temp->out && !temp->here_doc)
	// 	temp = temp->next;
	// if (temp && temp->here_doc)
	// {
	// 	ms_heredoc(temp, fd);
	// 	temp = temp->next;
	// }
	while (temp && temp->in)
	{
		// close(fd[0]);
		// close(fd[1]);
		// while (temp->next && temp->next->in)
		// {
		// 	infile = open(temp->path, O_RDONLY);
		// 	if (infile < 0)
		// 	{
		// 		perror(ft_strjoin("minishell: ", temp->cmd[0]));
		// 		exit(EXIT_FAILURE);
		// 	}
		// 	close(infile);
		// 	temp = temp->next;
		// }
		infile = open(temp->path, O_RDONLY);
		if (infile < 0)
		{
			perror(ft_strjoin("minishell: ", temp->cmd[0]));
			exit(EXIT_FAILURE);
		}
		if (temp && !temp->next->in)
			close (infile);
		temp = temp->next;
		// if (temp && temp->next->in)
		// {
		// 	close(fd[0]);
		// 	close(fd[1]);
		// 	exit(EXIT_SUCCESS);
		// }
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
		// if (temp->next && temp->next->out)
		// 	temp = temp->next;
	if (*prev_pipe != STDIN_FILENO)
	{
		dup2(*prev_pipe, STDIN_FILENO);
		close(*prev_pipe);
	}
	// exit (EXIT_SUCCESS);
}

void	setting_up_outs(t_pipe *temp, t_cmd *args, int (*fd), int *prev_out)
{
	int	outfile;

	(void)args;
	// if (temp->next && temp->next->out && !temp->out)
	// 	temp = temp->next;
	while (temp && temp->out)
	{
		// while (temp->next && temp->next->out)
		// {
		// 	outfile = open(temp->cmd[0], O_RDWR| O_CREAT | O_TRUNC, 0666);
		// 	if (outfile < 0)
		// 	{
		// 		perror(ft_strjoin("minishell: ", temp->cmd[0]));
		// 		exit(EXIT_FAILURE);
		// 	}
		// 	close(outfile);
		// 	temp = temp->next;
		// }
		if (temp && temp->append)
			outfile = open(temp->cmd[0], O_RDWR | O_CREAT | O_APPEND, 0666);
		else
			outfile = open(temp->cmd[0], O_RDWR| O_CREAT | O_TRUNC, 0666);
		if (outfile < 0)
		{
			perror(ft_strjoin("minishell: ", temp->cmd[0]));
			exit(EXIT_FAILURE);
		}
		// if (temp && temp->next->out)
		// 	exit(EXIT_SUCCESS);
		if (temp && !temp->next->out)
			close(outfile);
		temp = temp->next;
	}
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	// if (temp->next && temp->next->in)
	// 	temp = temp->next;
		*prev_out = 1;
	if (temp && temp->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	// exit (EXIT_SUCCESS);
}
