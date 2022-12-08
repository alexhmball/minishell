/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_up_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 03:52:47 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/08 20:16:32 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	ms_heredoc(t_pipe *temp, int (*fd))
// {
// 	char	**saving;
// 	char	*here_doc;
// 	int		here_doc_len;
// 	int		typed_len;
// 	int		i;

// 	here_doc_len = 0;
// 	typed_len = 0;
// 	here_doc_len = ft_strlen(temp->cmd[0]);
// 	saving = ft_calloc(1, 1);
// 	i = 0;
// 	// close(fd[0]);
// 	while (1)
// 	{
// 		here_doc = readline("> ");
// 		typed_len = ft_strlen(here_doc);
// 		saving = append_str(saving, here_doc);
// 		if (!ft_strncmp(temp->cmd[0], here_doc, typed_len) && typed_len == here_doc_len)
// 			break;
// 	}
// 	while (saving[i])
// 	{
// 		typed_len = ft_strlen(saving[i]);
// 		write(fd[1], saving[i], typed_len);
// 		i++;
// 	}
// 	dup2(fd[0], STDIN_FILENO);
// }

void	setting_up_ins(t_pipe *temp, int *prev_pipe, t_cmd *args, t_pipe *cmd, int ms_hd, int (*fd))
{
	int	infile;

	(void)ms_hd;
	if (temp->next && !temp->in && !temp->out && !temp->here_doc)
		temp = temp->next;
	if (temp && temp->here_doc)
	{
		ms_heredoc(temp, args, cmd, fd);
		temp = temp->next;
		// ms_hd = 1;
	}
	if (temp && temp->in)
	{
		while (temp->next && temp->next->in)
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
		if (temp->next && temp->next->out)
			temp = temp->next;
	}
	else if (*prev_pipe != STDIN_FILENO)
	{
		dup2(*prev_pipe, STDIN_FILENO);
		close(*prev_pipe);
	}
	// if (ms_hd)
	// {
	// 	dup2(fd[1], 0);
	// 	// close(fd[1]);
	// }
}

void	setting_up_outs(t_pipe *temp, t_cmd *args, int (*fd), int *prev_out)
{
	int	outfile;

	if (temp->next && temp->next->out && !temp->out)
		temp = temp->next;
	if (temp && temp->out)
	{
		while (temp->next && temp->next->out)
		{
			outfile = open(temp->cmd[0], O_RDWR| O_CREAT | O_TRUNC, 0666);
			if (outfile < 0)
			{
				perror(ft_strjoin("minishell: ", temp->cmd[0]));
				exit(EXIT_FAILURE);
			}
			close(outfile);
			temp = temp->next;
		}
		if (temp && temp->append)
			outfile = open(temp->cmd[0], O_RDWR | O_CREAT | O_APPEND, 0666);
		else
			outfile = open(temp->cmd[0], O_RDWR| O_CREAT | O_TRUNC, 0666);
		if (outfile < 0)
		{
			perror(ft_strjoin("minishell: ", temp->cmd[0]));
			exit(EXIT_FAILURE);
		}
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		if (temp->next && temp->next->in)
			temp = temp->next;
		*prev_out = 1;
	}
	else if (temp->next && args->pipe_n)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}
