/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:22:16 by aball             #+#    #+#             */
/*   Updated: 2022/11/10 23:11:40 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parsing(void)
{
	t_cmd	args;
	int		pid;
	char	*line;

	line = readline("\x1b[30m\x1b[46mminishell$\x1b[m ");
	if (!line)
	{
		free(line);
		exit (1);
	}
	if (line && *line)
		add_history(line);
	args.cmd = quote_validator(line, 0, 0);
	if (!args.cmd)
	{
		printf("Error: invalid quotes\n");
		return (1);
	}
	else if (ft_strlen(args.cmd[0]) == 4 && !ft_strncmp(args.cmd[0], "exit", 4))
	{
		printf("%s\n", args.cmd[0]);
		freedom(args.cmd);
		return (0);
	}
	else if (ft_strlen(args.cmd[0]) == 4 && !ft_strncmp(args.cmd[0], "echo", 4))
		my_echo(args.cmd);
	else if (ft_strlen(args.cmd[0]) == 3 && !ft_strncmp(args.cmd[0], "pwd", 3))
		print_working_dir();
	else if (ft_strlen(args.cmd[0]) == 2 && !ft_strncmp(args.cmd[0], "cd", 2))
		change_dir(args.cmd);
	else if (ft_strlen(args.cmd[0]) == 2 && !ft_strncmp(args.cmd[0], "ls", 2))
	{
		pid = fork();
		if (pid > 0)
			wait(NULL);
		else
		{
			args.path = "/bin/ls";
			execve(args.path, args.cmd, NULL);
		}
	}
	freedom(args.cmd);
	return (1);
}
