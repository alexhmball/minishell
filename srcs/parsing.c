/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:22:16 by aball             #+#    #+#             */
/*   Updated: 2022/10/24 12:54:28 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parsing(void)
{
	char	**cmd;
	char	*line;

	line = readline("\x1b[30m\x1b[46mminishell$\x1b[m ");
	if (!line)
		exit (0);
	if (line && *line)
		add_history(line);
	cmd = quote_validator(line, 0, 0);
	if (!cmd)
	{
		printf("Error: invalid quotes\n");
		return (1);
	}
	if (!ft_strncmp(cmd[0], "exit", 4) && ft_strlen(cmd[0]) == 4)
	{
		printf("%s\n", cmd[0]);
		freedom(cmd);
		return (0);
	}
	if (!ft_strncmp(cmd[0], "echo", 4) && ft_strlen(cmd[0]) == 4)
		my_echo(cmd);
	freedom(cmd);
	return (1);
}
