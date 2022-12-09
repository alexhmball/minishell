/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_up_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 03:52:47 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/09 23:32:30 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pipe	*setting_up_ins(t_pipe *temp)
{
	int	infile;

	while (temp && temp->in)
	{
		ft_putstr_fd("in\n", 2);
		infile = open(temp->path, O_RDONLY);
		if (infile < 0)
		{
			perror(ft_strjoin("minishell: ", temp->cmd[0]));
			exit(EXIT_FAILURE);
		}
		if (temp && temp->next && temp->next->in)
			close (infile);
		temp = temp->next;
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	return (temp);
}

t_pipe	*setting_up_outs(t_pipe *temp)
{
	int	outfile;

	while (temp && temp->out)
	{
		ft_putstr_fd("out\n", 2);
		if (temp && temp->append)
			outfile = open(temp->cmd[0], O_RDWR | O_CREAT | O_APPEND, 0666);
		else if (temp && temp->out)
			outfile = open(temp->cmd[0], O_RDWR| O_CREAT | O_TRUNC, 0666);
		if (outfile < 0)
		{
			perror(ft_strjoin("minishell: ", temp->cmd[0]));
			exit(EXIT_FAILURE);
		}
		if (temp && temp->next->out)
			close(outfile);
		temp = temp->next;
	}
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	return (temp);
}
