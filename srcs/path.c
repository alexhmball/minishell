/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:10:04 by aball             #+#    #+#             */
/*   Updated: 2022/11/15 22:42:52 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*parse_path(t_cmd *args, char *str)
{
	int		i;
	char	*ret;

	i = ft_strlen(str);
	while (str[i] != '/')
		i--;
	i++;
	ret = ft_strdup(str + i);
	args->path = ft_strdup(str);
	free (str);
	return (ret);
}

int	check_path(t_cmd *args)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (args->cmd[i])
	{
		j = 0;
		while (args->cmd[i][j])
		{
			if (args->cmd[i][j] == '/')
			{
				args->cmd[i] = parse_path(args, args->cmd[i]);
				flag = 1;
			}
			j++;
		}
		i++;
	}
	return (flag);
}

char	*check_single_path(char *cmd, t_cmd *args)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			cmd = parse_path(args, cmd);
		i++;
	}
	return (cmd);
}
