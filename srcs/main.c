/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:22:36 by aball             #+#    #+#             */
/*   Updated: 2022/12/11 01:43:18 by aball            ###   ########.fr       */
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
		if (info->si_status == 2 && info->si_code == 2)
			g_error = 130;
		else if (info->si_code == 1 && info->si_status == 2)
			g_error = 2;
		else if (info->si_code == 1 && info->si_status == 1
			&& g_error != 127 && g_error != 126)
			g_error = 1;
	}
	if (signo == SIGINT)
	{
		write(1, "\n\a", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_error != 130)
			rl_redisplay();
		g_error = 1;
	}
}

void	handle_this(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	signal(SIGINT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	t_cmd				args;

	(void)ac;
	(void)av;
	g_error = 0;
	args.sa.sa_sigaction = &handler;
	args.sa.sa_flags = SA_SIGINFO;
	sigemptyset(&args.sa.sa_mask);
	sigaction(SIGINT, &args.sa, NULL);
	sigaction(SIGCHLD, &args.sa, NULL);
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
