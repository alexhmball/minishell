/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:22:36 by aball             #+#    #+#             */
/*   Updated: 2022/11/25 18:03:45 by aball            ###   ########.fr       */
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
	// struct sigaction	sa;
	t_cmd				args;

	(void)ac;
	(void)av;
	// sa.sa_sigaction = &handler;
	// sa.sa_flags = SA_NOCLDSTOP;
	// sigemptyset(&sa.sa_mask);
	// sigaction(SIGINT, &sa, NULL);
	// signal(SIGQUIT, SIG_IGN);
	args.err = 0;
	if (!*env)
		printf("nope\n");
	args.env = create_env(env);
	args.env_for_excecute = env;
	while (1)
	{
		if (!parsing(&args))
			break ;
	}
	total_freedom(&args);
	return (args.err);
}
