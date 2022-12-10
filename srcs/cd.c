/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:36:24 by aball             #+#    #+#             */
/*   Updated: 2022/12/10 19:23:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	insert_env(char *env, char *path, t_cmd *args)
{
	t_env	*temp;
	int		len_env;
	int		len_find;

	temp = *args->env;
	len_env = ft_strlen(env) - 1;
	while (temp)
	{
		len_find = ft_strlen(temp->key);
		if (len_find == len_env && !ft_strncmp(env, temp->key, len_env))
		{
			my_free (temp->value);
			temp->value = ft_strdup(path);
			return ;
		}
		temp = temp->next;
	}
	env_addback(args->env, env_newlst(ft_strdup(env), path));
}

void	change_pwd_env(t_cmd *args, char **cmd, char *path)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = my_getenv("PWD", args);
	new_pwd = get_working_dir();
	insert_env("OLDPWD=", old_pwd, args);
	insert_env("PWD=", new_pwd, args);
	my_free(new_pwd);
	my_free(old_pwd);
	if (path != cmd[1])
		my_free(path);
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
		if (path != cmd[1])
			my_free(path);
		return ;
	}
	change_pwd_env(args, cmd, path);
}
