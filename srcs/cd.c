/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:36:24 by aball             #+#    #+#             */
/*   Updated: 2022/12/08 05:01:19 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	insert_env(char *env, char *path, t_cmd *args)
{
	t_list	*temp;
	int		len_env;
	int		len_find;

	temp = *args->env;
	len_env = ft_strlen(env) - 1;
	while (temp)
	{
		len_find = find_equal(temp->content);
		if (len_find == len_env && !ft_strncmp(env, temp->content, len_env))
		{
			my_free (temp->content);
			temp->content = ft_strjoin(env, path);
			return ;
		}
		temp = temp->next;
	}
	ft_lstadd_back(args->env, ft_lstnew(ft_strjoin(env, path)));
}

void	change_pwd_env(t_cmd *args)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = my_getenv("PWD", args);
	new_pwd = get_working_dir();
	insert_env("OLDPWD=", old_pwd, args);
	insert_env("PWD=", new_pwd, args);
	my_free(new_pwd);
	my_free(old_pwd);
}

void	change_dir(char **cmd, t_cmd *args)
{
	char	*path;

	if (two_d_strlen(cmd) > 1)
		path = cmd[1];
	else
		path = my_getenv("HOME", args);
	if (ft_strlen(path) == 1 && path[0] == '-')
	{
		path = my_getenv("OLDPWD", args);
		if (!path)
		{
			perror("minishell: cd");
			*args->err = 1;
			return ;
		}
	}
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		*args->err = 1;
		return ;
	}
	change_pwd_env(args);
}
