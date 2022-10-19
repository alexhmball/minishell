/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:22:16 by aball             #+#    #+#             */
/*   Updated: 2022/10/14 19:23:26 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parsing(void)
{
	char	*cmd;
	char	**args;

	cmd = readline("\x1b[30m\x1b[46mminishell$\x1b[m ");
	if (!cmd)
	{
		exit (0);
	}
	if (cmd && *cmd)
		add_history(cmd);
	if (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
	{
		printf("%s\n", cmd);
		free (cmd);
		return (0);
	}
	args = ft_split(cmd, ' ');
	if (!ft_strncmp(cmd, "echo[0]", 4) && ft_strlen(args[0]) == 4)
		my_echo(ft_split(cmd, ' '), 4);
	free (cmd);
	return (1);
}