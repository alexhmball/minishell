/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:30:34 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/11 07:28:43 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	here_sig(int signum)
{
	if (signum == SIGINT)
	{
		signal(SIGINT, SIG_DFL);
		kill(0, SIGINT);
		exit (0);
	}
}

char	**hd_saving_typed(t_pipe *temp)
{
	char	**saving;
	char	*here_doc;
	int		here_doc_len;
	int		typed_len;

	signal(SIGINT, here_sig);
	signal(SIGQUIT, SIG_IGN);
	here_doc_len = 0;
	typed_len = 0;
	here_doc_len = ft_strlen(temp->cmd[0]);
	saving = (char **)ft_calloc(1, sizeof(char *));
	if (temp && temp->here_doc)
	{
		while (1)
		{
			here_doc = readline("> ");
			typed_len = ft_strlen(here_doc);
			if ((!here_doc_len && typed_len == here_doc_len) || !here_doc)
				break ;
			if (here_doc_len && !ft_strncmp(temp->cmd[0], here_doc, typed_len)
				&& typed_len == here_doc_len)
				break ;
			saving = append_str(saving, here_doc);
		}
	}
	return (saving);
}

void	ms_heredoc(t_pipe *temp, t_cmd *args)
{
	char	**saved;
	int		saved_len;
	int		i;

	saved_len = 0;
	i = 0;
	close(args->fd[0]);
	saved = hd_saving_typed(temp);
	while (saved[i])
	{
		saved_len = ft_strlen(saved[i]);
		write(args->fd[1], saved[i], saved_len);
		write(args->fd[1], "\n", 1);
		i++;
	}
	freedom(saved);
	dup2(args->fd[1], STDOUT_FILENO);
	close(args->fd[1]);
	lstclear_pipe(args->pipe, my_free);
	total_freedom(args);
	exit (EXIT_SUCCESS);
}
