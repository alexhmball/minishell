/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:30:34 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/08 18:54:36 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_heredoc(t_pipe *temp, int (*fd))
{
	char	**saving;
	char	*here_doc;
	int		here_doc_len;
	int		typed_len;
	int		i;
	int		child;

	child = fork();
	if (!child)
	{	
		here_doc_len = 0;
		typed_len = 0;
		here_doc_len = ft_strlen(temp->cmd[0]);
		saving = ft_calloc(1, 1);
		i = 0;
		close(fd[0]);
		while (1)
		{
			here_doc = readline("> ");
			typed_len = ft_strlen(here_doc);
			saving = append_str(saving, here_doc);
			if (!ft_strncmp(temp->cmd[0], here_doc, typed_len) && typed_len == here_doc_len)
				break;
		}
		dup2(fd[1], STDOUT_FILENO);
		while (saving[i])
		{
			typed_len = ft_strlen(saving[i]);
			write(fd[1], saving[i], typed_len);
			i++;
		}
	}
	wait(NULL);
	close(fd[1]);
	// temp = temp->next;
	return ;
}