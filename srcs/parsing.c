/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:22:16 by aball             #+#    #+#             */
/*   Updated: 2022/11/27 01:43:32 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parse_pipe(t_cmd *args)
{
	t_pipe	*temp;
	t_pipe	*prev;
	int		i;

	i = 0;
	if (!flag_list(args))
		return (0);
	find_cmd_args(args);
	// 	temp = *args->pipe;
	// while (temp)
	// {
	// 	i = 0;
	// 	while (temp->cmd[i])
	// 	{
	// 		printf("cmd: %s\n", temp->cmd[i++]);
	// 	}
	// 	printf("path: %s\n", temp->path);
	// 	printf("pipe? %d\n", temp->is_pipe);
	// 	printf("in? %d\n", temp->in);
	// 	printf("out? %d\n", temp->out);
	// 	printf(".....\n");
	// 	temp = temp->next;
	// }
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
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
	if (args->need_exp)
		check_expand(args);
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
	if (ft_strlen(args->cmd[0]) == 4 && !ft_strncmp(args->cmd[0], "exit", 4))
	{
		ft_printf("%s\n", args->cmd[0]);
		return (0);
	}
	// else if (is_us(args))
	// 	excecute_us(args);
	else /*if (check_dir(args) || check_path(args))*/
	{
		// execute_them(args);
		create_pipe_list(args);
		if (!parse_pipe(args))
			return (args->err);
		args->pid = fork();
		if (args->pid == 0)
		{
			pipex(args);
			while (waitpid(-1, &args->pid, 0) > 0)
				;
			exit(args->err);
		}
		waitpid(-1, &args->pid, 0);
	}
	// freedom(args->cmd);
	// my_free(args->s);
	// my_free(args->expand);
	// my_free(args->path);
	return (1);
}
