/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:30:34 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/08 20:16:01 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_heredoc(t_pipe *temp, t_cmd *args, t_pipe *cmd, int (*fd))
{
	(void)cmd;
	char	**saving;
	char	*here_doc;
	int		here_doc_len;
	int		typed_len;
	int		i;

	here_doc_len = 0;
	typed_len = 0;
	here_doc_len = ft_strlen(temp->cmd[0]);
	saving = ft_calloc(1, 1);
	i = 0;
	// close(fd[0]);
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
	close(fd[1]);
	return ;
}