/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:10:35 by aball             #+#    #+#             */
/*   Updated: 2022/12/10 19:18:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	us_not_printing(t_cmd *args)
{
	t_pipe	*c;

	c = *args->pipe;
	while (c && !c->here_doc)
	{
		if (ft_strlen(c->cmd[0]) == 2 && !ft_strncmp(c->cmd[0], "cd", 2))
		{
			change_dir(c->cmd, args);
			freedom(c->cmd);
			c->cmd = (char **)malloc(sizeof(char *) * 2);
			c->cmd[0] = ft_strdup("exit");
			c->cmd[1] = NULL;
			args->flag = 1;
		}
		else if (ft_strlen(c->cmd[0]) == 6
			&& !ft_strncmp(c->cmd[0], "export", 6) && two_d_strlen(c->cmd) > 1)
			my_export(args, c);
		else if (ft_strlen(c->cmd[0]) == 5
			&& !ft_strncmp(c->cmd[0], "unset", 5))
			my_unset(args, c);
		else if (ft_strlen(c->cmd[0]) == 4 && !ft_strncmp(c->cmd[0], "exit", 4))
			exit_shell(args, c);
		c = c->next;
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
		my_unset(args, cmd);
	else if (ft_strlen(cmd->cmd[0]) == 4
		&& !ft_strncmp(cmd->cmd[0], "exit", 4))
		exit_shell(args, cmd);
}

void	execute_them(t_cmd *args, t_pipe *cmd)
{
	if (!cmd->path)
	{
		*args->err = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (access(cmd->path, X_OK) != 0)
	{
		set_error(args, errno);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else
	{
		execve(cmd->path, cmd->cmd, args->env_for_excecute);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	executioner(args);
}
