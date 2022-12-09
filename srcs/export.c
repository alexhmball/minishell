/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:53:39 by aball             #+#    #+#             */
/*   Updated: 2022/12/09 23:23:34 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	compare_env(t_cmd *args, t_pipe *node, char *key, char *value)
{
	t_env	*current;
	int		len;
	int		len_env;

	current = *args->env;
	len = ft_strlen(key);
	if (two_d_strlen(node->cmd) > 1 && len != -1)
	{
		while (current)
		{
			len_env = ft_strlen(current->key);
			if (len_env == len)
			{
				if (!ft_strncmp(current->key, key, len))
				{
					my_free(current->value);
					current->value = value;
					return (1);
				}
			}
			current = current->next;
		}
	}
	return (0);
}

void	print_env(t_env *env)
{
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value)
			printf("=\"%s\"\n", env->value);
		else
			printf("\n");
		env = env->next;
	}
}

void	my_export(t_cmd *args, t_pipe *node)
{
	t_env	*temp;
	char	*key;
	char	*value;

	temp = *args->env;
	key = get_key(node->cmd[1]);
	value = get_value(node->cmd[1]);
	if (two_d_strlen(node->cmd) > 1 && value
		&& !compare_env(args, node, key, value))
	{
		while (temp)
		{
			if (ft_strlen(temp->key) == ft_strlen(key)
				&& !ft_strncmp(temp->value, value, ft_strlen(value)))
				return ;
			temp = temp->next;
		}
		if (find_equal(node->cmd[1]) != -1)
			env_addback(args->env, env_newlst(key, value));
	}
	else if (two_d_strlen(node->cmd) > 1 && !value)
		env_addback(args->env, env_newlst(key, NULL));
	else if (two_d_strlen(node->cmd) <= 1)
		print_env(*args->env);
}
