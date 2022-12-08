/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:10:04 by aball             #+#    #+#             */
/*   Updated: 2022/12/08 22:49:11 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	check_single_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	confirm_path(t_cmd *args)
{
	t_pipe	*temp;

	temp = *args->pipe;
	while (temp)
	{
		if (check_single_path(temp->cmd[0]))
		{
			temp->path = ft_strdup(temp->cmd[0]);
		}
		else if (!temp->path)
			temp->path = NULL;
		temp = temp->next;
	}
}
