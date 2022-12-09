/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:22:36 by aball             #+#    #+#             */
/*   Updated: 2022/12/09 23:45:34 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_error;

void	handler(int signo, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signo == SIGSEGV)
	{
		printf("Segmentation fault, chuckle fuck!\n");
		exit(139);
	}
	if (signo == SIGCHLD)
	{
		// waitpid(-1, NULL, WNOHANG);
		wait(NULL);
		if (info->si_status == 2 && info->si_code == 2)
			g_error = 130;
		else if (info->si_code == 1 && info->si_status == 2)
			g_error = 2;
		else if (info->si_code == 1 && info->si_status == 1
			&& g_error != 127 && g_error != 126)
			g_error = 1;
		// printf("\ncode: %d pid: %d err: %s\n", info->si_code, info->si_pid, strerror(info->si_errno));
		// if (info->si_code == CLD_KILLED)
		// 	printf("Killed by signal\n");
		// if (info->si_code == CLD_DUMPED)
		// 	printf("Killed by signal and dumped core\n");
		// if (info->si_code == CLD_TRAPPED)
		// 	printf("Traced by debugger\n");
		// if (info->si_code == CLD_STOPPED)
		// 	printf("Stopped by signal\n");
		// if (info->si_code == CLD_CONTINUED)
		// 	printf("Continued\n");
		// printf("status: %d\n", info->si_status);
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

int	main(int ac, char **av, char **env)
{
	struct sigaction	sa;
	t_cmd				args;

	(void)ac;
	(void)av;
	g_error = 0;
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	// sigaddset(&sa.sa_mask, SIGINT);
	// sigaddset(&sa.sa_mask, SIGCHLD);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGCHLD, &sa, NULL);
	sigaction(SIGSEGV, &sa, NULL);
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
