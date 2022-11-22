/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:22:16 by aball             #+#    #+#             */
/*   Updated: 2022/11/22 01:40:56 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_pipe_list(t_cmd *args)
{
	t_pipe	*temp;
	int		i;

	i = 0;
	args->pipe = (t_pipe **)malloc(sizeof(t_pipe *));
	validate_path(args->cmd[i], args);
	args->cmd[i] = check_single_path(args->cmd[i], args);
	temp = lstnew_pipe(args->cmd[i], args->path);
	my_free(args->path);
	*args->pipe = temp;
	temp->next = NULL;
	i++;
	while (args->cmd[i])
	{
		if (validate_path(args->cmd[i], args) && args->cmd[i - 1][0] != '>' && args->cmd[i - 1][0] != '<')
		{
			args->cmd[i] = check_single_path(args->cmd[i], args);
			lstadd_back_pipe(args->pipe, lstnew_pipe(args->cmd[i], args->path));
			my_free(args->path);
			temp = temp->next;
		}
		else if (args->cmd[i][0] == '|')
		{
			validate_path(args->cmd[i], args);
			args->cmd[i] = check_single_path(args->cmd[i], args);
			lstadd_back_pipe(args->pipe, lstnew_pipe(args->cmd[i], args->path));
			my_free(args->path);
			temp = temp->next;
			temp->is_pipe = 1;
			i++;
			if (args->cmd[i])
			{
				validate_path(args->cmd[i], args);
				args->cmd[i] = check_single_path(args->cmd[i], args);
				lstadd_back_pipe(args->pipe, lstnew_pipe(args->cmd[i], args->path));
				my_free(args->path);
				temp = temp->next;
			}
		}
		else if (args->cmd[i][0] == '>' || args->cmd[i][0] == '<')
		{
			validate_path(args->cmd[i], args);
			args->cmd[i] = check_single_path(args->cmd[i], args);
			lstadd_back_pipe(args->pipe, lstnew_pipe(args->cmd[i], args->path));
			my_free(args->path);
			temp = temp->next;
		}
		else
			temp->cmd = append_str(temp->cmd, args->cmd[i]);
		i++;
	}
}

void	print_pipe_list(t_cmd *args)
{
	t_pipe	*temp;
	int		i;
	int		c;

	temp = *args->pipe;
	i = 0;
	c = 0;
	while (temp)
	{
		if (temp->next && !temp->path && !temp->next->is_pipe && !temp->is_pipe)
			swap_node(temp, temp->next, args->pipe, c);
		c++;
		temp = temp->next;
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
		printf(".....\n");
		temp = temp->next;
	}
	lstclear_pipe(args->pipe, free);
	free(args->pipe);
}

int	parsing(t_cmd *args)
{
	int		pid;

	init_struct(args);
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
	if (args->pipe_n || args->redirect)
	{
		create_pipe_list(args);
		print_pipe_list(args);
		// lstclear_pipe(args->pipe, free);
	}
	else if (ft_strlen(args->cmd[0]) == 4 && !ft_strncmp(args->cmd[0], "exit", 4))
	{
		ft_printf("%s\n", args->cmd[0]);
		return (0);
	}
	else if (ft_strlen(args->cmd[0]) == 4 && !ft_strncmp(args->cmd[0], "echo", 4))
		my_echo(args->cmd, args);
	else if (ft_strlen(args->cmd[0]) == 3 && !ft_strncmp(args->cmd[0], "pwd", 3))
		print_working_dir();
	else if (ft_strlen(args->cmd[0]) == 2 && !ft_strncmp(args->cmd[0], "cd", 2))
		change_dir(args->cmd, args);
	else if (ft_strlen(args->cmd[0]) == 6 && !ft_strncmp(args->cmd[0], "export", 6))
		my_export(args);
	else if (ft_strlen(args->cmd[0]) == 3 && !ft_strncmp(args->cmd[0], "env", 3))
		my_env(args);
	else if (ft_strlen(args->cmd[0]) == 5 && !ft_strncmp(args->cmd[0], "unset", 5))
		my_unset(args);
	else if (check_dir(args) || check_path(args))
	{
		if (!args->path)
		{
			args->err = 127;
			printf("minishell: %s: command not found\n", args->cmd[0]);
		}
		else if (access(args->path, X_OK) != 0)
		{
			set_error(args, errno);
			printf("minishell: %s: %s\n", args->path, strerror(errno));
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				execve(args->path, args->cmd, NULL);
				printf("minishell: %s: no such file or directory here\n", args->path);
				exit (127);
			}
			wait(&pid);
			// if (kill(pid, SIGQUIT) < 0)
			// 	kill(pid, SIGTERM);
		}
	}
	freedom(args->cmd);
	free(args->s);
	free(args->expand);
	free(args->path);
	args->expand = NULL;
	return (1);
}
