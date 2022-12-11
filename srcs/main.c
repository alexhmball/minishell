/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:22:36 by aball             #+#    #+#             */
/*   Updated: 2022/12/12 02:55:52 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_error;

void	sig_igor(int sig)
{
	(void)sig;
	write(1, "\n", 1);
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
		else if (info->si_status == 3 && info->si_code == 3)
			g_error = 131;
		else if (info->si_status > 100)
			g_error = info->si_status;
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

void	handle_this(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	g_error = -420;
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
	sigemptyset(&pid.sa_mask);
	args.sa.sa_sigaction = &handler;
	args.sa.sa_flags = SA_SIGINFO;
	sigemptyset(&args.sa.sa_mask);
	sigaction(SIGINT, &args.sa, NULL);
	sigaction(SIGCHLD, &args.sa, NULL);
	sigaction(SIGUSR1, &pid, NULL);
	kill(0, SIGUSR1);
	args.pid = g_error;
	g_error = 0;
	args.err = &g_error;
	args.env = create_env(env);
	args.env_for_excecute = twd_d_strdup(env);
	while (1)
		if (!parsing(&args))
			break ;
	total_freedom(&args);
	return (*args.err);
}
