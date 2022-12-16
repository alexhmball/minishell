/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:22:36 by aball             #+#    #+#             */
/*   Updated: 2022/12/16 07:31:00 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_error;

static void	initializer(t_cmd *args, char **env)
{
	args->pid = g_error;
	g_error = 0;
	args->err = &g_error;
	args->env_for_excecute = twd_d_strdup(env);
	args->env = create_env(env, args);
}

int	main(int ac, char **av, char **env)
{
	t_cmd				args;

	(void)av;
	if (ac > 1)
	{
		printf("minishell: no arguments will be accepted\n");
		return (0);
	}
	args.sa.sa_sigaction = &handler;
	args.sa.sa_flags = SA_SIGINFO;
	sigemptyset(&args.sa.sa_mask);
	sigaction(SIGINT, &args.sa, NULL);
	sigaction(SIGCHLD, &args.sa, NULL);
	initializer(&args, env);
	while (1)
		if (!parsing(&args))
			break ;
	total_freedom(&args);
	return (*args.err);
}
