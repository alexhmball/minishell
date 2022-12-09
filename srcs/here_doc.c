/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:30:34 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/09 22:52:24 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_heredoc(t_pipe *temp, int (*fd), t_cmd *args)
{
	char	**saving;
	char	*here_doc;
	int		here_doc_len;
	int		typed_len;
	int		i;

	here_doc_len = 0;
	typed_len = 0;
	here_doc_len = ft_strlen(temp->cmd[0]);
	saving = (char **)ft_calloc(1, sizeof(char *));
	i = 0;
	close(fd[0]);
	if (temp && temp->here_doc)
	{
		while (1)
		{
			here_doc = readline("> ");
			if (!here_doc)
				break ;
			typed_len = ft_strlen(here_doc);
			if (!ft_strncmp(temp->cmd[0], here_doc, typed_len) && typed_len == here_doc_len)
				break ;
			saving = append_str(saving, here_doc);
		}
	}
	if (args->heredoc_n > 1)
		exit(EXIT_SUCCESS);
	while (saving[i])
	{
		typed_len = ft_strlen(saving[i]);
		write(fd[1], saving[i], typed_len);
		write(fd[1], "\n", 1);
		i++;
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exit (EXIT_SUCCESS);
}
