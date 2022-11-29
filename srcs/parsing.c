/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:22:16 by aball             #+#    #+#             */
/*   Updated: 2022/11/29 18:40:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_rangler(int signo, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n\a");
		rl_redisplay();
		kill(info->si_pid, SIGQUIT);
	}
}

void	confirm_path(t_cmd *args)
{
	t_pipe	*temp;

	temp = *args->pipe;
	while (temp)
	{
		temp->cmd[0] = check_single_path(temp->cmd[0], args);
		if (args->path)
			temp->path = ft_strdup(args->path);
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
	temp = *args->pipe;
	while (temp)
	{
		i = 0;
		while (temp->cmd[i])
		{
			printf("cmd: %s\n", temp->cmd[i++]);
		}
		printf("path: %s\n", temp->path);
		printf("pipe? %d\n", temp->is_pipe);
		printf("in? %d\n", temp->in);
		printf("out? %d\n", temp->out);
		printf(".....\n");
		temp = temp->next;
	}
	confirm_path(args);
	find_cmd_args(args);
	organize_cmds(args);
	temp = *args->pipe;
	while (temp)
	{
		if (temp->next && temp->is_pipe)
			temp = remove_node(args->pipe, temp, prev, i);
		prev = temp;
		temp = temp->next;
		i++;
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	temp = *args->pipe;
	while (temp)
	{
		i = 0;
		while (temp->cmd[i])
		{
			printf("cmd: %s\n", temp->cmd[i++]);
		}
		printf("path: %s\n", temp->path);
		printf("pipe? %d\n", temp->is_pipe);
		printf("in? %d\n", temp->in);
		printf("out? %d\n", temp->out);
		printf("single? %d\n", temp->single_q);
		printf("double? %d\n", temp->double_q);
		printf(".....\n");
		temp = temp->next;
	}
	return (1);
}

int	parsing(t_cmd *args)
{
	init_struct(args);
	rl_redisplay();
	args->s = readline("\x1b[30m\x1b[46mminishell$\x1b[m ");
	if (!args->s)
		return (0);
	if (args->s && *args->s)
		add_history(args->s);
	else
		return (1);
	args->expand = (int *)ft_calloc(count_dollar(args->s), sizeof(int));
	args->cmd = quote_validator(args, 0, 0);
	if (!args->cmd)
	{
		printf("minishell: Error: invalid quotes\n");
		return (1);
	}
	// if (args->need_exp)
	// 	check_expand(args);
	// if (args->pipe_n || args->redirect)
	// {
		// create_pipe_list(args);
		// if (!print_pipe_list(args))
		// 	return (args->err);
		// args->pid = fork();
		// if (args->pid == 0)
		// 	pipex(args);
		// wait(&args->pid);
		// lstclear_pipe(args->pipe, my_free);
	// }
	// if (ft_strlen(args->cmd[0]) == 4 && !ft_strncmp(args->cmd[0], "exit", 4))
	// {
	// 	ft_printf("%s\n", args->cmd[0]);
	// 	return (0);
	// }
	// else if (is_us(args))
	// 	excecute_us(args);
	else /*if (check_dir(args) || check_path(args))*/
	{
		struct sigaction	sig;

		sig.sa_sigaction = &child_rangler;
		sig.sa_flags = SA_NOCLDSTOP;
		sigemptyset(&sig.sa_mask);
		// execute_them(args);
		create_pipe_list(args);
		if (!parse_pipe(args))
			return (args->err);
		// args->pid = fork();
		// if (args->pid == 0)
		// {
		// 	sigaction(SIGINT, &sig, NULL);
		// 	pipex(args);
		// 	while (waitpid(-1, &args->pid, 0) > 0)
		// 		;
		// 	exit(args->err);
		// }
		// waitpid(-1, &args->pid, 0);
	}
	// freedom(args->cmd);
	// my_free(args->s);
	// my_free(args->expand);
	// my_free(args->path);
	return (1);
}
