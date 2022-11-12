/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:59:19 by aball             #+#    #+#             */
/*   Updated: 2022/11/12 23:37:01 by aball            ###   ########.fr       */
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
	while (current)
	{
		if (ft_strlen(current->content) >= 4
			&& !ft_strncmp(current->content, "PATH", 4))
			break ;
		current = current->next;
	}
	ret = ft_split(current->content + 5, ':');
	return (ret);
}

int	search_dir(t_cmd *args, char **search, int i)
{
	if (ft_strlen(args->dir->d_name) == ft_strlen(args->cmd[0])
		&& !ft_strncmp(args->dir->d_name, args->cmd[0],
			ft_strlen(args->dir->d_name)))
	{
		args->path = ft_strjoin(search[i], "/");
		args->path = ft_strjoin(args->path, args->cmd[0]);
		closedir(args->folder);
		return (1);
	}
	args->dir = readdir(args->folder);
	return (0);
}

int	check_dir(t_cmd *args)
{
	char	**search;
	int		i;

	i = 0;
	search = find_path(args);
	if (!search)
		return (0);
	while (search[i])
	{
		args->folder = opendir(search[i]);
		if (!args->folder)
		{
			printf("%s: command not found\n", args->cmd[0]);
			return (0);
		}
		args->dir = readdir(args->folder);
		while (args->dir)
			if (search_dir(args, search, i))
				return (1);
		closedir(args->folder);
		i++;
	}
	printf("%s: command not found\n", args->cmd[0]);
	closedir(args->folder);
	return (0);
}