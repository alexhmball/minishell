/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:22:16 by aball             #+#    #+#             */
/*   Updated: 2022/11/11 22:41:53 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_dir(t_cmd *args)
{
	args->folder = opendir("/bin");
	args->dir = readdir(args->folder);
	while (args->dir)
	{
		if (args->dir->d_namlen == ft_strlen(args->cmd[0]) && !ft_strncmp(args->dir->d_name, args->cmd[0], args->dir->d_namlen))
		{
			args->path = ft_strjoin("/bin/", args->cmd[0]);
			return ;
		}
		args->dir = readdir(args->folder);
	}
	args->folder = opendir("/usr/bin");
	if (!args->folder)
		printf("fucked\n");
	args->dir = readdir(args->folder);
	while (args->dir)
	{
		if (args->dir->d_namlen == ft_strlen(args->cmd[0])  && !ft_strncmp(args->dir->d_name, args->cmd[0], args->dir->d_namlen))
		{
			args->path = ft_strjoin("/usr/bin/", args->cmd[0]);
			return ;
		}
		args->dir = readdir(args->folder);
	}
	printf("%s: command not found\n", args->cmd[0]);
}

int	parsing(t_cmd *args)
{
	int		pid;

	args->line = readline("\x1b[30m\x1b[46mminishell$\x1b[m ");
	if (!args->line)
	{
		free(args->line);
		exit (1);
	}
	args->expand = (int *)ft_calloc(count_dollar(args->line), sizeof(int));
	if (args->line && *args->line)
		add_history(args->line);
	else
		return (1);
	args->cmd = quote_validator(args, 0, 0);
	if (!args->cmd)
	{
		printf("Error: invalid quotes\n");
		return (1);
	}
	if (args->need_exp)
		check_expand(args);
	if (ft_strlen(args->cmd[0]) == 4 && !ft_strncmp(args->cmd[0], "exit", 4))
	{
		printf("%s\n", args->cmd[0]);
		freedom(args->cmd);
		return (0);
	}
	else if (ft_strlen(args->cmd[0]) == 4 && !ft_strncmp(args->cmd[0], "echo", 4))
		my_echo(args->cmd);
	else if (ft_strlen(args->cmd[0]) == 3 && !ft_strncmp(args->cmd[0], "pwd", 3))
		print_working_dir();
	else if (ft_strlen(args->cmd[0]) == 2 && !ft_strncmp(args->cmd[0], "cd", 2))
		change_dir(args->cmd);
	else if (ft_strlen(args->cmd[0]) == 6 && !ft_strncmp(args->cmd[0], "export", 6))
		my_export(args);
	else if (ft_strlen(args->cmd[0]) == 3 && !ft_strncmp(args->cmd[0], "env", 3))
		my_env(args);
	else if (ft_strlen(args->cmd[0]) == 5 && !ft_strncmp(args->cmd[0], "unset", 5))
		my_unset(args);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			check_dir(args);
			execve(args->path, args->cmd, NULL);
			exit (1);
		}
		else
		{
			wait(&pid);
			kill(pid, SIGQUIT);
		}
	}
	freedom(args->cmd);
	return (1);
}
