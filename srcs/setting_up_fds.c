/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_up_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 03:52:47 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/11/29 20:03:14 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pipe	*setting_up_ins(t_pipe *temp, int *prev_pipe)
{
	int	infile;

	if (temp->in)
	{
		while (temp->next->in)
		{
			infile = open(temp->path, O_RDONLY);
			if (infile < 0)
			{
				perror(ft_strjoin("minishell: ", temp->cmd[0]));
				exit(EXIT_FAILURE);
			}
			close(infile);
			temp = temp->next;
		}
		infile = open(temp->path, O_RDONLY);
		if (infile < 0)
		{
			perror(ft_strjoin("minishell: ", temp->cmd[0]));
			exit(EXIT_FAILURE);
		}
		dup2(infile, STDIN_FILENO);
		close(infile);
		temp = temp->next;
	}
	if (*prev_pipe != STDIN_FILENO)
	{
		dup2(*prev_pipe, STDIN_FILENO);
		close(*prev_pipe);
	}
	return (temp);
}

t_pipe	*setting_up_outs(t_pipe *temp, t_cmd *args, int (*fd), int *prev_out)
{
	int	outfile;

	if (temp && temp->out)
	{
		printf("hello again\n");
		while (temp->next && temp->next->out)
		{
			printf("mfker never loved us\n");
			outfile = open(temp->cmd[0], O_RDWR| O_CREAT | O_TRUNC, 0666);
			if (outfile < 0)
			{
				perror(ft_strjoin("minishell: ", temp->cmd[0]));
				exit(EXIT_FAILURE);
			}
			close(outfile);
			temp = temp->next;
		}
		printf("cmd in out: %s\n", temp->cmd[0]);
		outfile = open(temp->cmd[0], O_RDWR| O_CREAT | O_TRUNC, 0666);
		if (outfile < 0)
		{
			perror(ft_strjoin("minishell: ", temp->cmd[0]));
			exit(EXIT_FAILURE);
		}
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		// temp = temp->next;
		*prev_out = 1;
	}
	if (*prev_out == 0 && args->pipe_n && temp->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	return (temp);
}