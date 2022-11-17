/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:36:24 by aball             #+#    #+#             */
/*   Updated: 2022/11/17 18:40:37 by ballzball        ###   ########.fr       */
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
			free (temp->content);
			temp->content = ft_strjoin(env, path);
		}
		temp = temp->next;
	}
}

void	change_pwd_env(t_cmd *args)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = my_getenv("PWD", args);
	new_pwd = get_working_dir();
	insert_env("OLDPWD=",old_pwd, args);
	insert_env("PWD=",new_pwd, args);
	free(new_pwd);
	free(old_pwd);
}

void	change_dir(char **cmd, t_cmd *args)
{
	char	*path;

	if (two_d_strlen(cmd) > 1)
		path = cmd[1];
	else
		path = my_getenv("HOME", args);
	if (chdir(path) != 0)
	{
		if (errno == ENOTDIR)
			printf("minishell: cd: %s: Not a directory\n", cmd[1]);
		if (errno == ENOENT)
			printf("minishell: cd: %s: No such file or directory\n", cmd[1]);
		if (errno == EACCES)
			printf("minishell: cd: %s: Permission denied\n", cmd[1]);
		return ;
	}
	change_pwd_env(args);
}
