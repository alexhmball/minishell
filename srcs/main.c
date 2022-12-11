/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:22:36 by aball             #+#    #+#             */
/*   Updated: 2022/12/11 05:12:14 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_error;

void	sig_igor(int sig)
{
	(void)sig;
	write(1, "Quit: 3\n", 8);
	g_error = 131;
	signal(SIGQUIT, SIG_DFL);
}

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
		// else if (info->si_status > 2)
		// 	g_error = info->si_status;
		// printf("status = %d code = %d\n", info->si_status, info->si_code);
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

void	get_pid_me(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	g_error = info->si_pid;
}

int	main(int ac, char **av, char **env)
{
	t_cmd				args;
	struct sigaction	pid;

	(void)ac;
	(void)av;
	pid.sa_flags = SA_SIGINFO;
	pid.sa_sigaction = &get_pid_me;
	args.sa.sa_sigaction = &handler;
	args.sa.sa_flags = SA_SIGINFO;
	sigemptyset(&args.sa.sa_mask);
	sigaction(SIGINT, &args.sa, NULL);
	sigaction(SIGCHLD, &args.sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGUSR1, &pid, NULL);
	kill(0, SIGUSR1);
	args.pid = g_error;
	g_error = 0;
	args.err = &g_error;
	args.env = create_env(env);
	args.env_for_excecute = env;
	while (1)
		if (!parsing(&args))
			break ;
	total_freedom(&args);
	return (*args.err);
}
