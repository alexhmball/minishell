/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:53:39 by aball             #+#    #+#             */
/*   Updated: 2022/12/11 13:42:46 by ballzball        ###   ########.fr       */
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
					current->value = ft_strdup(value);
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

void	find_export(t_env **head, char *key, char *value, t_pipe *node)
{
	t_env	*temp;

	temp = *head;
	while (temp)
	{
		if (ft_strlen(temp->key) == ft_strlen(key)
			&& !ft_strncmp(temp->value, value, ft_strlen(value)))
		{
			my_free(key);
			my_free(value);
			return ;
		}
		temp = temp->next;
	}
	if (find_equal(node->cmd[1]) != -1)
		env_addback(head, env_newlst(ft_strdup(key),
				ft_strdup(value)));
}

void	my_export(t_cmd *args, t_pipe *node)
{
	char	*key;
	char	*value;

	key = get_key(node->cmd[1]);
	value = get_value(node->cmd[1]);
	if (two_d_strlen(node->cmd) > 1 && value
		&& !compare_env(args, node, key, value))
		find_export(args->env, key, value, node);
	else if (two_d_strlen(node->cmd) > 1 && !value)
		env_addback(args->env, env_newlst(ft_strdup(key), NULL));
	else if (two_d_strlen(node->cmd) <= 1)
		print_env(*args->env);
	my_free(key);
	my_free(value);
	args->env_for_excecute = make_env_for_ex(args->env, args->env_for_excecute);
}
