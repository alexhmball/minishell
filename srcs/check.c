/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:59:19 by aball             #+#    #+#             */
/*   Updated: 2022/12/10 18:46:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**find_path(t_cmd *args)
{
	char	**ret;
	t_env	*current;

	current = *args->env;
	ret = NULL;
	while (current)
	{
		if (ft_strlen(current->key) == 4
			&& !ft_strncmp(current->key, "PATH", 4))
			break ;
		current = current->next;
	}
	if (current)
		ret = ft_split(current->value, ':');
	return (ret);
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
	if (!search)
		return (0);
	current = get_working_dir();
	search = append_str(search, current);
	my_free(current);
	while (search[i])
	{
		if (searching_dirs(search[i], args, cmd, search))
			return (1);
		i++;
	}
	freedom(search);
	args->path = NULL;
	return (0);
}
