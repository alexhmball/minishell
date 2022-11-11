/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:22:36 by aball             #+#    #+#             */
/*   Updated: 2022/11/12 02:09:25 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handler(int signo, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	int					ret;
	struct sigaction	sa;
	t_cmd				*args;

	(void)ac;
	(void)av;
	args = (t_cmd *)malloc(sizeof(t_cmd));
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	args->env = create_env(env);
	while (1)
	{
		ret = parsing(args);
		if (ret == 0)
			exit (0);
	}
	ft_lstclear(args->env, free);
	free(args->env);
	free(args->line);
	freedom(args->cmd);
	free(args->expand);
	rl_clear_history();
	return (0);
}
