/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:36:24 by aball             #+#    #+#             */
/*   Updated: 2022/12/13 22:23:38 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	insert_env(char *env, char *path, t_cmd *args)
{
	t_env	*temp;
	int		len_env;
	int		len_find;

	temp = *args->env;
	if (!path)
		return ;
	len_env = ft_strlen(env);
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
	env_addback(args->env, env_newlst(ft_strdup(env), ft_strdup(path)));
}

void	change_pwd_env(t_cmd *args, char **cmd, char *path)
{
	char	*old_pwd;
	char	*new_pwd;

	(void)cmd;
	old_pwd = my_getenv("PWD", args);
	new_pwd = get_working_dir();
	insert_env("OLDPWD", old_pwd, args);
	insert_env("PWD", new_pwd, args);
	my_free(new_pwd);
	my_free(path);
	my_free(old_pwd);
}

void	change_dir(char **cmd, t_cmd *args)
{
	char	*path;

	if (two_d_strlen(cmd) > 1)
		path = ft_strdup(cmd[1]);
	else
	{
		path = my_getenv("HOME", args);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			*args->err = 1;
			return ;
		}
	}
	if (ft_strlen(path) == 1 && path[0] == '-')
	{
		my_free(path);
		path = my_getenv("OLDPWD", args);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			*args->err = 1;
			return ;
		}
		printf("%s\n", path);
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
