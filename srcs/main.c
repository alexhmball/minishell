/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:22:36 by aball             #+#    #+#             */
/*   Updated: 2022/11/14 11:17:33 by aball            ###   ########.fr       */
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
	total_freedom(args);
	return (0);
}
