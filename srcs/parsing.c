/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:22:16 by aball             #+#    #+#             */
/*   Updated: 2022/10/23 22:35:49 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parsing(void)
{
	char	*cmd;
	char	*line;
	char	**args;

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
	if (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
	{
		printf("%s\n", cmd);
		free (cmd);
		return (0);
	}
	args = special_split(cmd);
	if (!ft_strncmp(args[0], "echo", 4) && ft_strlen(args[0]) == 4)
		my_echo(args);
	free (cmd);
	freedom(args);
	return (1);
}
