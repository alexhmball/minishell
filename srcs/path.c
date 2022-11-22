/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:10:04 by aball             #+#    #+#             */
/*   Updated: 2022/11/22 18:43:48 by aball            ###   ########.fr       */
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
	my_free (str);
	return (ret);
}

int	check_path(t_cmd *args)
{
	int	i;
	int	j;

	i = 0;
	while (args->cmd[i])
	{
		j = 0;
		while (args->cmd[i][j])
		{
			if (args->cmd[i][j] == '/')
				args->cmd[i] = parse_path(args, args->cmd[i]);
			j++;
		}
		i++;
	}
	return (1);
}

int	search_dir(t_cmd *args, char *search)
{
	char	*temp;

	if (ft_strlen(args->dir->d_name) == ft_strlen(args->cmd[0])
		&& !ft_strncmp(args->dir->d_name, args->cmd[0],
			ft_strlen(args->dir->d_name)))
	{
		temp = ft_strjoin(search, "/");
		args->path = ft_strjoin(temp, args->cmd[0]);
		closedir(args->folder);
		my_free (temp);
		return (1);
	}
	args->dir = readdir(args->folder);
	return (0);
}

int	search_all_paths(t_cmd *args, char **search)
{
	int		i;

	i = 0;
	while (search[i])
	{
		args->folder = opendir(search[i]);
		if (args->folder)
		{
			args->dir = readdir(args->folder);
			while (args->dir)
			{
				if (search_dir(args, search[i]))
					return (freedom(search));
			}
			closedir(args->folder);
		}
		i++;
	}
	return (0);
}

int	search_current_dir(t_cmd *args, char *current)
{
	args->folder = opendir(current);
	if (args->folder)
	{
		args->dir = readdir(args->folder);
		while (args->dir)
		{
			if (search_dir(args, current))
			{
				my_free(current);
				return (1);
			}
		}
		closedir(args->folder);
	}
	return (0);
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
