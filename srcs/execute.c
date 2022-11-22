/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:10:35 by aball             #+#    #+#             */
/*   Updated: 2022/11/23 01:28:30 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_us(t_cmd *args)
{
	if (ft_strlen(args->cmd[0]) == 4 && !ft_strncmp(args->cmd[0], "echo", 4))
		return (1);
	else if (ft_strlen(args->cmd[0]) == 3
		&& !ft_strncmp(args->cmd[0], "pwd", 3))
		return (1);
	else if (ft_strlen(args->cmd[0]) == 2 && !ft_strncmp(args->cmd[0], "cd", 2))
		return (1);
	else if (ft_strlen(args->cmd[0]) == 6
		&& !ft_strncmp(args->cmd[0], "export", 6))
		return (1);
	else if (ft_strlen(args->cmd[0]) == 3
		&& !ft_strncmp(args->cmd[0], "env", 3))
		return (1);
	else if (ft_strlen(args->cmd[0]) == 5
		&& !ft_strncmp(args->cmd[0], "unset", 5))
		return (1);
	return (0);
}

void	excecute_us(t_cmd *args)
{
	if (ft_strlen(args->cmd[0]) == 4 && !ft_strncmp(args->cmd[0], "echo", 4))
		my_echo(args->cmd, args);
	else if (ft_strlen(args->cmd[0]) == 3
		&& !ft_strncmp(args->cmd[0], "pwd", 3))
		print_working_dir();
	else if (ft_strlen(args->cmd[0]) == 2 && !ft_strncmp(args->cmd[0], "cd", 2))
		change_dir(args->cmd, args);
	else if (ft_strlen(args->cmd[0]) == 6
		&& !ft_strncmp(args->cmd[0], "export", 6))
		my_export(args);
	else if (ft_strlen(args->cmd[0]) == 3
		&& !ft_strncmp(args->cmd[0], "env", 3))
		my_env(args);
	else if (ft_strlen(args->cmd[0]) == 5
		&& !ft_strncmp(args->cmd[0], "unset", 5))
		my_unset(args);
}

void	execute_them(t_cmd *args)
{
	int	pid;

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
			printf("minishell: %s: no such file or directory\n", args->path);
			exit (127);
		}
		wait(&pid);
		kill(pid, SIGQUIT);
	}
}
