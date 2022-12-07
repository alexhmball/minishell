/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:22:36 by aball             #+#    #+#             */
/*   Updated: 2022/12/07 20:27:36 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_error;

void	handler(int signo, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signo == SIGCHLD)
	{
		if (info->si_code == 2)
		{
			g_error = 130;
			write(1, "\n\a", 2);
		}
		else
			g_error = 0;
			return ;
	}
	if (signo == SIGINT)
	{
		write(1, "\n\a", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_error = 1;
	}
}


int	main(int ac, char **av, char **env)
{
	struct sigaction	sa;
	t_cmd				args;

	(void)ac;
	(void)av;
	g_error = 0;
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_NOCLDSTOP;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGCHLD);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGCHLD, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	args.err = &g_error;
	args.env = create_env(env);
	args.env_for_excecute = env;
	while (1)
		if (!parsing(&args))
			break ;
	total_freedom(&args);
	return (*args.err);
}
