/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:30:34 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/17 02:47:35 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	breaking_heredoc(int d_len, int t_len, char *typed, t_pipe *temp)
{
	if ((!d_len && t_len == d_len) || !typed)
		return (1);
	if (d_len && !ft_strncmp(temp->cmd[0], typed, t_len) && t_len == d_len)
		return (1);
	return (0);
}

void	here_sig(int signum, siginfo_t *info, void *context)
{
	static t_cmd	*args;

	(void)info;
	if (signum == SIGUSR2)
		args = (t_cmd *)context;
	else if (signum == SIGINT)
	{
		g_error = -420;
		lstclear_pipe(args->pipe, my_free);
		freedom(args->saving);
		total_freedom(args);
		signal(SIGINT, SIG_DFL);
		kill(0, SIGINT);
		exit (0);
	}
}

char	**hd_saving_typed(t_pipe *temp, t_cmd *args)
{
	char				*typed;
	int					delimiter_len;
	int					typed_len;
	struct sigaction	act;

	act.sa_sigaction = &here_sig;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
	delimiter_len = ft_strlen(temp->cmd[0]);
	args->saving = (char **)ft_calloc(1, sizeof(char *));
	here_sig(SIGUSR2, NULL, args);
	if (temp && temp->here_doc)
	{
		while (1)
		{
			typed = readline("> ");
			typed_len = ft_strlen(typed);
			if (breaking_heredoc(delimiter_len, typed_len, typed, temp))
				break ;
			args->saving = append_str(args->saving, typed);
		}
	}
	return (args->saving);
}

void	ms_heredoc(t_pipe *temp, t_cmd *args, int prev_pipe)
{
	char	**saved;
	int		saved_len;
	int		i;

	saved_len = 0;
	i = 0;
	close(args->fd[0]);
	saved = hd_saving_typed(temp, args);
	while (saved[i])
	{
		saved_len = ft_strlen(saved[i]);
		write(args->fd[1], saved[i], saved_len);
		write(args->fd[1], "\n", 1);
		i++;
	}
	freedom(saved);
	close(prev_pipe);
	dup2(args->fd[1], STDOUT_FILENO);
	close(args->fd[1]);
	lstclear_pipe(args->pipe, my_free);
	total_freedom(args);
	exit (EXIT_SUCCESS);
}
