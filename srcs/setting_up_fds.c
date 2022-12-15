/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_up_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 03:52:47 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/15 08:03:32 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_error_messages(t_cmd *args, t_pipe *temp, int redir)
{
	if ((redir < 0 || !temp->path) && temp->in && temp)
	{
		if (!temp->path)
			ft_putstr_fd("minishell: No such file or directory\n", 2);
		else
			ft_putstr_fd("minishell: Permission denied\n", 2);
		lstclear_pipe(args->pipe, my_free);
		total_freedom(args);
		exit(EXIT_FAILURE);
	}
	if (redir < 0 && (temp->out || temp->append) && temp)
	{
		ft_putstr_fd("minishell: Permission denied\n", 2);
		lstclear_pipe(args->pipe, my_free);
		total_freedom(args);
		exit(EXIT_FAILURE);
	}
	if (redir == -420 && temp)
	{
		perror("pipe: ");
		lstclear_pipe(args->pipe, my_free);
		total_freedom(args);
		exit(EXIT_FAILURE);
	}
}

t_pipe	*setting_up_ins(t_pipe *temp, t_cmd *args, int prev_pipe)
{
	int	infile;

	infile = -1;
	while (temp && temp->in)
	{
		if (temp->path)
			infile = open(temp->path, O_RDONLY);
		ms_error_messages(args, temp, infile);
		if (temp && temp->next && (temp->next->in || temp->next->here_doc))
			close (infile);
		temp = temp->next;
	}
	if (temp && temp->here_doc)
		ms_heredoc(temp, args, prev_pipe);
	dup2(infile, STDIN_FILENO);
	close(infile);
	close(args->fd[0]);
	return (temp);
}

t_pipe	*setting_up_outs(t_pipe *temp, t_cmd *args)
{
	int	outfile;

	outfile = -1;
	while (temp && (temp->out || temp->append))
	{
		if (temp && temp->append)
			outfile = open(temp->cmd[0], O_RDWR | O_CREAT | O_APPEND, 0666);
		else if (temp && temp->out)
			outfile = open(temp->cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0666);
		ms_error_messages(args, temp, outfile);
		if (temp && temp->next && (temp->next->out || temp->next->append))
			close(outfile);
		temp = temp->next;
	}
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	return (temp);
}
