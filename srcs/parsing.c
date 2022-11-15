/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:22:16 by aball             #+#    #+#             */
/*   Updated: 2022/11/15 17:11:11 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_pipe_list(t_cmd *args)
{
	t_pipe	*temp;
	int		i;

	i = 0;
	args->pipe = (t_pipe **)malloc(sizeof(t_pipe *));
	validate_path(args->cmd, args->path, args);
	temp = lstnew_pipe(args->cmd[i], args->path);
	*args->pipe = temp;
	i++;
	while (args->cmd[i])
	{
		if (args->cmd[i][0] == '|')
		{
			validate_path(args->cmd, args->path, args);
			lstadd_back_pipe(args->pipe, lstnew_pipe(args->cmd[i], args->path));
			temp = temp->next;
			i++;
			if (args->cmd[i])
			{
				validate_path(args->cmd, args->path, args);
				lstadd_back_pipe(args->pipe, lstnew_pipe(args->cmd[i], args->path));
			}
			temp = temp->next;
		}
		else if (args->cmd[i][0] == '>' || args->cmd[i][0] == '<')
		{
			validate_path(args->cmd, args->path, args);
			lstadd_back_pipe(args->pipe, lstnew_pipe(args->cmd[i], args->path));
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

	temp = *args->pipe;
	i = 0;
	while (temp)
	{
		i = 0;
		while (temp->cmd[i])
		{
			printf("cmd: %s\n", temp->cmd[i++]);
		}
			printf(".....\n");
		// printf("path: %s\n", temp->path);
		temp = temp->next;
	}
}

int	parsing(t_cmd *args)
{
	int		pid;

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
		printf("Error: invalid quotes\n");
		return (1);
	}
	if (args->need_exp)
		check_expand(args);
	if (args->pipe_n)
	{
		create_pipe_list(args);
		print_pipe_list(args);
	}
	if (ft_strlen(args->cmd[0]) == 4 && !ft_strncmp(args->cmd[0], "exit", 4))
	{
		ft_printf("%s\n", args->cmd[0]);
		return (0);
	}
	else if (ft_strlen(args->cmd[0]) == 4 && !ft_strncmp(args->cmd[0], "echo", 4))
		my_echo(args->cmd);
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
	else if (check_dir(args))
	{
		pid = fork();
		if (pid == 0)
		{
			execve(args->path, args->cmd, NULL);
			printf("%s: no such file or directory\n", args->cmd[0]);
			exit (1);
		}
		else
		{
			// free(args->path);
			wait(&pid);
			kill(pid, SIGQUIT);
		}
	}
	freedom(args->cmd);
	free(args->s);
	free(args->expand);
	return (1);
}
