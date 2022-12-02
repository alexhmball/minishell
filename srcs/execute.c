/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:10:35 by aball             #+#    #+#             */
/*   Updated: 2022/12/02 23:49:42 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	return (0);
}

void	excecute_us(t_cmd *args, int fd, t_pipe *cmd)
{
	if (ft_strlen(cmd->cmd[0]) == 4 && !ft_strncmp(cmd->cmd[0], "echo", 4))
		my_echo(cmd->cmd, args, fd);
	else if (ft_strlen(cmd->cmd[0]) == 3
		&& !ft_strncmp(cmd->cmd[0], "pwd", 3))
		print_working_dir(fd);
	else if (ft_strlen(cmd->cmd[0]) == 2 && !ft_strncmp(cmd->cmd[0], "cd", 2))
		change_dir(cmd->cmd, args);
	else if (ft_strlen(cmd->cmd[0]) == 6
		&& !ft_strncmp(cmd->cmd[0], "export", 6))
		my_export(args, fd);
	else if (ft_strlen(cmd->cmd[0]) == 3
		&& !ft_strncmp(cmd->cmd[0], "env", 3))
		my_env(args, fd);
	else if (ft_strlen(cmd->cmd[0]) == 5
		&& !ft_strncmp(cmd->cmd[0], "unset", 5))
		my_unset(args);
}

void	execute_them(t_cmd *args, t_pipe *cmd)
{
	if (!cmd->path)
	{
		args->err = 127;
		perror(ft_strjoin("minishell: ", /*args->cmd[0]*/strerror(errno)));
		exit(EXIT_FAILURE);
	}
	else if (access(cmd->path, X_OK) != 0)
	{
		set_error(args, errno);
		perror(ft_strjoin("minishell: ", /*args->path, */strerror(errno)));
		exit(EXIT_FAILURE);
	}
	else
	{
		execve(cmd->path, cmd->cmd, args->env_for_excecute);
		perror(ft_strjoin("minishell: ", strerror(errno)));
		exit(EXIT_FAILURE);
	}
}
