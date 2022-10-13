/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:22:16 by aball             #+#    #+#             */
/*   Updated: 2022/10/13 17:57:58 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	valid_quotes(char *cmd)
{
	int i;
	int	single;
	int	dub;

	i = 0;
	single = 0;
	dub = 0;
	while (cmd[i])
	{
		if (cmd[i] == 39)
			single++;
		if (cmd[i] == 34)
			dub++;
		i++;
	}
	if (single % 2 == 0 && dub % 2 == 0)
		return (true);
	return (false);
}

int	parsing(void)
{
	char	*cmd;

	cmd = readline("\x1b[30m\x1b[46mminishell$\x1b[m ");
	if (!cmd)
	{
		exit (0);
	}
	if (cmd && *cmd)
		add_history(cmd);
	if (!valid_quotes(cmd))
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
	if (!ft_strncmp(cmd, "echo -n", 7))
		my_echo(cmd, 7);
	else if (!ft_strncmp(cmd, "echo", 4))
		my_echo(cmd, 4);
	free (cmd);
	return (1);
}