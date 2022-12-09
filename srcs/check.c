/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:59:19 by aball             #+#    #+#             */
/*   Updated: 2022/12/09 16:39:30 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**find_path(t_cmd *args)
{
	char	**ret;
	t_list	*current;

	current = *args->env;
	ret = NULL;
	while (current)
	{
		if (ft_strlen(current->content) >= 4
			&& !ft_strncmp(current->content, "PATH", 4))
			break ;
		current = current->next;
	}
	if (current)
		ret = ft_split(current->content + 5, ':');
	return (ret);
}

int	check_dir(t_cmd *args)
{
	char	**search;
	char	*current;

	search = find_path(args);
	if (!search)
	{
		args->path = NULL;
		return (1);
	}
	if (search_all_paths(args, search))
		return (1);
	current = get_working_dir();
	if (search_current_dir(args, current))
		return (1);
	*args->err = 127;
	freedom(search);
	my_free(current);
	args->path = NULL;
	return (0);
}

int	validate_dir(t_cmd *args, char *search, char *cmd)
{
	char	*temp;

	if (ft_strlen(args->dir->d_name) == ft_strlen(cmd)
		&& !ft_strncmp(args->dir->d_name, cmd,
			ft_strlen(args->dir->d_name)))
	{
		temp = ft_strjoin(search, "/");
		args->path = ft_strjoin(temp, cmd);
		my_free (temp);
		closedir(args->folder);
		return (1);
	}
	args->dir = readdir(args->folder);
	return (0);
}

int	searching_dirs(char *search, t_cmd *args, char *cmd, char **delete)
{
	args->folder = opendir(search);
	if (args->folder)
	{
		args->dir = readdir(args->folder);
		while (args->dir)
		{
			if (validate_dir(args, search, cmd))
			{
				freedom(delete);
				return (1);
			}
		}
		closedir(args->folder);
	}
	return (0);
}

int	validate_path(char *cmd, t_cmd *args)
{
	char	**search;
	char	*current;
	int		i;

	i = 0;
	search = find_path(args);
	current = get_working_dir();
	search = append_str(search, current);
	my_free(current);
	if (!search)
		return (0);
	while (search[i])
	{
		if (searching_dirs(search[i], args, cmd, search))
			return (1);
		i++;
	}
	args->path = NULL;
	return (0);
}
