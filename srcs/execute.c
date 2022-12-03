/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:10:35 by aball             #+#    #+#             */
/*   Updated: 2022/12/03 04:36:26 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	us_not_printing(t_cmd *args)
{
	t_pipe	*cmd;

	cmd = *args->pipe;
	while (cmd)
	{
		if (ft_strlen(cmd->cmd[0]) == 2 && !ft_strncmp(cmd->cmd[0], "cd", 2))
		{
			change_dir(cmd->cmd, args);
			freedom(cmd->cmd);
			cmd->cmd = (char **)malloc(sizeof(char *) * 2);
			cmd->cmd[0] = ft_strdup("exit");
			cmd->cmd[1] = NULL;
		}
		else if (ft_strlen(cmd->cmd[0]) == 6
			&& !ft_strncmp(cmd->cmd[0], "export", 6) && two_d_strlen(cmd->cmd) > 1)
			my_export(args, cmd);
		else if (ft_strlen(cmd->cmd[0]) == 5
			&& !ft_strncmp(cmd->cmd[0], "unset", 5))
			my_unset(args);
		cmd = cmd->next;
	}
}

int	is_us(t_pipe *cmd)
{
	if (ft_strlen(cmd->cmd[0]) == 4 && !ft_strncmp(cmd->cmd[0], "echo", 4))
		return (1);
	else if (ft_strlen(cmd->cmd[0]) == 3
		&& !ft_strncmp(cmd->cmd[0], "pwd", 3))
		return (1);
	else if (ft_strlen(cmd->cmd[0]) == 2 && !ft_strncmp(cmd->cmd[0], "cd", 2))
		return (1);
	else if (ft_strlen(cmd->cmd[0]) == 6
		&& !ft_strncmp(cmd->cmd[0], "export", 6))
		return (1);
	else if (ft_strlen(cmd->cmd[0]) == 3
		&& !ft_strncmp(cmd->cmd[0], "env", 3))
		return (1);
	else if (ft_strlen(cmd->cmd[0]) == 5
		&& !ft_strncmp(cmd->cmd[0], "unset", 5))
		return (1);
	else if (ft_strlen(cmd->cmd[0]) == 4
		&& !ft_strncmp(cmd->cmd[0], "exit", 4))
		return (1);
	return (0);
}

void	excecute_us(t_cmd *args, t_pipe *cmd)
{
	if (ft_strlen(cmd->cmd[0]) == 4 && !ft_strncmp(cmd->cmd[0], "echo", 4))
		my_echo(cmd->cmd, args);
	else if (ft_strlen(cmd->cmd[0]) == 3
		&& !ft_strncmp(cmd->cmd[0], "pwd", 3))
		print_working_dir();
	else if (ft_strlen(cmd->cmd[0]) == 2 && !ft_strncmp(cmd->cmd[0], "cd", 2))
		change_dir(cmd->cmd, args);
	else if (ft_strlen(cmd->cmd[0]) == 6
		&& !ft_strncmp(cmd->cmd[0], "export", 6))
		my_export(args, cmd);
	else if (ft_strlen(cmd->cmd[0]) == 3
		&& !ft_strncmp(cmd->cmd[0], "env", 3))
		my_env(args);
	else if (ft_strlen(cmd->cmd[0]) == 5
		&& !ft_strncmp(cmd->cmd[0], "unset", 5))
		my_unset(args);
	else if (ft_strlen(cmd->cmd[0]) == 4
		&& !ft_strncmp(cmd->cmd[0], "exit", 4))
		exit_shell(args, cmd);
}

void	execute_them(t_cmd *args, t_pipe *cmd)
{
	if (!cmd->path)
	{
		args->err = 127;
		perror(ft_strjoin("minishell: ", /*args->cmd[0]*/strerror(errno)));
		// exit(EXIT_FAILURE);
	}
	else if (access(cmd->path, X_OK) != 0)
	{
		set_error(args, errno);
		perror(ft_strjoin("minishell: ", /*args->path, */strerror(errno)));
		// exit(EXIT_FAILURE);
	}
	else
	{
		// int fuck = fork();
		// if (!fuck)
		// {
			execve(cmd->path, cmd->cmd, args->env_for_excecute);
			perror(ft_strjoin("minishell: ", strerror(errno)));
			exit(EXIT_FAILURE);
		// }
	}
}
