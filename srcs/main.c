/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:22:36 by aball             #+#    #+#             */
/*   Updated: 2022/12/05 18:37:31 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handler(int signo, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signo == SIGCHLD && info->si_status == 2)
	{
		// rl_replace_line("", 0);
		write(1, "\n", 1);
		// printf("\n\a");
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
		// kill(info->si_pid, SIGINT);
		// return ;
	}
	else if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n\a");
		rl_redisplay();
		// printf("%d\n", info->si_pid);
		// printf("%d\n", info->si_status);
		// printf("%d\n", info->si_code);
		// printf("%ld\n", info->si_band);
		// printf("%d\n", info->si_errno);
		// // printf("%d\n", info->si_value);
		// printf("%d\n", info->si_uid);
		// printf("%d\n", info->si_addr);
	}
}

int	main(int ac, char **av, char **env)
{
	struct sigaction	sa;
	t_cmd				args;

	(void)ac;
	(void)av;
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_NOCLDSTOP;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	// sigaction(SIGCHLD, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	args.err = 0;
	args.env = create_env(env);
	args.env_for_excecute = env;
	while (1)
		if (!parsing(&args))
			break ;
	total_freedom(&args);
	return (args.err);
}
