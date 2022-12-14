/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_up_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 03:52:47 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/13 15:59:11 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pipe	*setting_up_ins(t_pipe *temp, t_cmd *args)
{
	int	infile;

	infile = -1;
	while (temp && temp->in)
	{
		if (temp->path)
			infile = open(temp->path, O_RDONLY);
		if (infile < 0 || !temp->path)
		{
			ft_putstr_fd("minishell: No such file or directory\n", 2);
			lstclear_pipe(args->pipe, my_free);
			total_freedom(args);
			exit(EXIT_FAILURE);
		}
		if (temp && temp->next && (temp->next->in || temp->next->here_doc))
			close (infile);
		temp = temp->next;
	}
	if (temp && temp->here_doc)
		ms_heredoc(temp, args);
	dup2(infile, STDIN_FILENO);
	close(infile);
	close(args->fd[0]);
	return (temp);
}

t_pipe	*setting_up_outs(t_pipe *temp, t_cmd *args)
{
	int	outfile;

	(void)args;
	while (temp && temp->out)
	{
		if (temp && temp->append)
			outfile = open(temp->cmd[0], O_RDWR | O_CREAT | O_APPEND, 0666);
		else if (temp && temp->out)
			outfile = open(temp->cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (outfile < 0)
		{
			perror(temp->cmd[0]);
			lstclear_pipe(args->pipe, my_free);
			total_freedom(args);
			exit(EXIT_FAILURE);
		}
		if (temp && (temp->next->out || temp->next->append))
			close(outfile);
		temp = temp->next;
	}
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	return (temp);
}
