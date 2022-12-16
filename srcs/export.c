/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:53:39 by aball             #+#    #+#             */
/*   Updated: 2022/12/16 15:10:59 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	compare_env(t_cmd *args, t_pipe *node, char *key, char *value)
{
	t_env	*current;
	int		len;
	int		len_env;

	(void)node;
	current = *args->env;
	len = ft_strlen(key);
	while (current)
	{
		len_env = ft_strlen(current->key);
		if (len_env == len)
		{
			if (!ft_strncmp(current->key, key, len))
			{
				my_free(current->value);
				current->value = ft_strdup(value);
				my_free(key);
				my_free(value);
				return (1);
			}
		}
		current = current->next;
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
			&& !ft_strncmp(temp->value, value, ft_strlen(value))
			&& !ft_strncmp(temp->key, key, ft_strlen(key)))
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
	my_free(key);
	my_free(value);
}

int	check_key(char *key)
{
	int	i;

	i = 0;
	if (!key || !*key)
		return (0);
	if (ft_isdigit(key[i]))
	{
		printf("minishell: export: %s: not a valid identifier\n", key);
		my_free(key);
		return (0);
	}
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			printf("minishell: export: %s: not a valid identifier\n", key);
			my_free(key);
			return (0);
		}
		i++;
	}
	return (1);
}

void	my_export(t_cmd *args, t_pipe *node)
{
	char	*key;
	char	*value;
	size_t	i;

	i = 0;
	while (node->cmd[++i])
	{
		key = get_key(node->cmd[i]);
		value = get_value(node->cmd[i]);
		if (check_key(key))
		{
			if (value && !compare_env(args, node, key, value))
				find_export(args->env, key, value, node);
			else if (!value && !compare_env(args, node, key, value))
			{
				env_addback(args->env, env_newlst(ft_strdup(key), NULL));
				my_free(key);
			}
		}
		else if (value)
			my_free(value);
	}
	if (two_d_strlen(node->cmd) <= 1)
		print_env(*args->env);
	args->env_for_excecute = make_env_for_ex(args->env, args->env_for_excecute);
}
