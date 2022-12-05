/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:22:16 by aball             #+#    #+#             */
/*   Updated: 2022/12/03 21:02:05 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_rangler(int signo, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signo == SIGCHLD)
	{
		// printf("\n\a");
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
		// signal(SIGINT, SIG_IGN);
		// kill(info->si_pid, SIGINT);
		// printf("%d\n", info->si_pid);
		// printf("%d\n", info->si_status);
		// printf("%d\n", info->si_code);
		kill(info->si_pid, SIGTERM);
		exit (0);
	}
}

void	confirm_path(t_cmd *args)
{
	t_pipe	*temp;

	temp = *args->pipe;
	while (temp)
	{
		if (check_single_path(temp->cmd[0]))
		{
			temp->path = ft_strdup(temp->cmd[0]);
		}
		else if (!temp->path)
			temp->path = NULL;
		temp = temp->next;
	}
}

int	parse_pipe(t_cmd *args)
{
	t_pipe	*temp;
	t_pipe	*prev;
	int		i;

	i = 0;
	if (!flag_list(args))
		return (0);
	find_cmd_args(args);
	organize_cmds(args);
	desperation(args);
	temp = *args->pipe;
	args->pipe_n = 0;
	while (temp)
	{
		if (temp->next && temp->is_pipe)
		{
			temp = remove_node(args->pipe, temp, prev, i);
			args->pipe_n++;
		}
		prev = temp;
		temp = temp->next;
		i++;
	}
	temp = *args->pipe;
	i = 0;
	while (temp)
	{
		if (temp->next && temp->next->here_doc && !temp->here_doc)
		{
			swap_node(temp, temp->next, args->pipe, i);
			temp = *args->pipe;
			prev = NULL;
			i = -1;
		}
		if (i > -1)
		{
			prev = temp;
			temp = temp->next;
		}
		i++;
	}
	confirm_path(args);
	// print_pipe(args->pipe);
	return (1);
}

int	parsing(t_cmd *args)
{
	init_struct(args);
	args->s = readline("\x1b[30m\x1b[46mminishell$\x1b[m ");
	if (!args->s)
		return (0);
	if (args->s && *args->s)
		add_history(args->s);
	else
		return (1);
	args->cmd = quote_validator(args, 0, 0);
	if (!args->cmd)
	{
		printf("minishell: Error: invalid quotes\n");
		return (1);
	}
	if (!ft_strncmp(args->cmd[0], "exit", 4) && two_d_strlen(args->cmd) == 1 && ft_strlen(args->cmd[0]) == 4)
	{
		ft_printf("%s\n", args->cmd[0]);
		return (0);
	}
	else
	{
		create_pipe_list(args);
		if (!parse_pipe(args))
			return (args->err);
		if (!args->pipe_n)
			us_not_printing(args);
		args->pid = fork();
		if (args->pid == 0)
		{
			struct sigaction	act;

			act.sa_sigaction = child_rangler;
			act.sa_flags = SA_SIGINFO;
			sigemptyset(&act.sa_mask);
			sigaction(SIGCHLD, &act, NULL);
			// signal(SIGINT, SIG_IGN);
			// sigaction(SIGINT, &act, NULL);
			pipex(args);
			while (waitpid(-1, &args->pid, WIFSTOPPED) > 0)
				;
			lstclear_pipe(args->pipe, my_free);
			exit(args->err);
		}
		waitpid(-1, &args->pid, WIFSTOPPED);
		lstclear_pipe(args->pipe, my_free);
	}
	my_free(args->s);
	return (1);
}
