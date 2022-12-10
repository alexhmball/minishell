/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_up_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 03:52:47 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/11 01:48:55 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pipe	*setting_up_ins(t_pipe *temp, t_cmd *args)
{
	int	infile;

	while (temp && temp->in)
	{
		infile = open(temp->path, O_RDONLY);
		if (infile < 0)
		{
			perror(ft_strjoin("minishell: ", temp->cmd[0]));
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
			perror(ft_strjoin("minishell: ", temp->cmd[0]));
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
