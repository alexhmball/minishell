/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:59:19 by aball             #+#    #+#             */
/*   Updated: 2022/11/18 22:49:11 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*my_getenv(char *str_env, t_cmd *args)
{
	t_list	*current;
	size_t		len;
	size_t			len2;

	current = *args->env;
	len = ft_strlen(str_env);
	while (current)
	{
		len2 = find_equal(current->content);
		if (len2 == len && !ft_strncmp(current->content, str_env, len))
			return (ft_strdup(current->content + len + 1));
		current = current->next;
	}
	return (NULL);
}

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
		free (temp);
		return (1);
	}
	args->dir = readdir(args->folder);
	return (0);
}

int	check_dir(t_cmd *args)
{
	char	**search;
	char	*current;
	int		i;

	i = 0;
	search = find_path(args);
	if (!search)
	{
		args->path = NULL;
		return (1);
	}
	while (search[i])
	{
		args->folder = opendir(search[i]);
		if (args->folder)
		{
			args->dir = readdir(args->folder);
			while (args->dir)
				if (search_dir(args, search[i]))
				{
					freedom(search);
					return (1);
				}
			closedir(args->folder);
		}
		i++;
	}
	current = get_working_dir();
	args->folder = opendir(current);
	if (args->folder)
	{
		args->dir = readdir(args->folder);
		while (args->dir)
			if (search_dir(args, current))
			{
				free(current);
				freedom(search);
				return (1);
			}
		closedir(args->folder);
	}
	if (*args->cmd)
		printf("minishell: %s: command not found\n", args->cmd[0]);
	args->err = 127;
	freedom(search);
	free(current);
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
		free (temp);
		closedir(args->folder);
		return (1);
	}
	args->dir = readdir(args->folder);
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
	while (search[i])
	{
		args->folder = opendir(search[i]);
		if (args->folder)
		{
			args->dir = readdir(args->folder);
			while (args->dir)
				if (validate_dir(args, search[i], cmd))
				{
					freedom(search);
					return (1);
				}
			closedir(args->folder);
		}
		i++;
	}
	current = get_working_dir();
	args->folder = opendir(current);
	if (args->folder)
	{
		args->dir = readdir(args->folder);
		while (args->dir)
			if (validate_dir(args, current, cmd))
			{
				free(current);
				freedom(search);
				return (1);
			}
		closedir(args->folder);
	}
	free(current);
	freedom(search);
	args->path = NULL;
	return (0);
}
