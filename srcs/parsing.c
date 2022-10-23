/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:22:16 by aball             #+#    #+#             */
/*   Updated: 2022/10/23 18:46:38 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*quote_validator(char *line)
{
	int	i;
	int	single_q;
	int	double_q;

	i = 0;
	single_q = 0;
	double_q = 0;
	while (line[i])
	{
		if (line[i] == '"' && !single_q && !double_q)
			double_q = 1;
		else if (line[i] == 39 && !single_q && !double_q)
			single_q = 1;
		else if (line[i] == '"' && !single_q && double_q)
			double_q = 0;
		else if (line[i] == 39 && single_q && !double_q)
			single_q = 0;
		i++;
	}
	if (!single_q && !double_q)
		return ("a");
	return (NULL);
}

int	parsing(void)
{
	char	*cmd;
	char	**args;

	cmd = readline("\x1b[30m\x1b[46mminishell$\x1b[m ");
	if (!cmd)
	{
		exit (0);
	}
	if (!quote_validator(cmd))
		printf("Error: invalid quotes\n");
	if (cmd && *cmd)
		add_history(cmd);
	if (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
	{
		printf("%s\n", cmd);
		free (cmd);
		return (0);
	}
	args = ft_split(cmd, ' ');
	// if (!ft_strncmp(&cmd[0], "echo", 4) && ft_strlen(args[0]) == 4)
	// 	my_echo(ft_split(cmd, ' '));
	free (cmd);
	return (1);
}