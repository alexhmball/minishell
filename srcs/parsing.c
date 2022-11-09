/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:22:16 by aball             #+#    #+#             */
/*   Updated: 2022/11/09 19:05:54 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parsing(void)
{
	char	**cmd;
	char	*line;

	line = readline("\x1b[30m\x1b[46mminishell$\x1b[m ");
	if (!line)
	{
		free(line);
		exit (1);
	}
	if (line && *line)
		add_history(line);
	cmd = quote_validator(line, 0, 0);
	if (!cmd)
	{
		printf("Error: invalid quotes\n");
		return (1);
	}
	else if (ft_strlen(cmd[0]) == 4 && !ft_strncmp(cmd[0], "exit", 4))
	{
		printf("%s\n", cmd[0]);
		freedom(cmd);
		return (0);
	}
	else if (ft_strlen(cmd[0]) == 4 && !ft_strncmp(cmd[0], "echo", 4))
		my_echo(cmd);
	else if (ft_strlen(cmd[0]) == 3 && !ft_strncmp(cmd[0], "pwd", 3))
		print_working_dir();
	else if (ft_strlen(cmd[0]) == 2 && !ft_strncmp(cmd[0], "cd", 2))
		change_dir(cmd);
	else
	{
		cmd[0] = "bin/ls";
		execve(cmd[0], cmd, NULL);
	}
	// freedom(cmd);
	return (1);
}
