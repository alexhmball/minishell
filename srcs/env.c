/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:37:28 by aball             #+#    #+#             */
/*   Updated: 2022/12/09 21:48:34 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*my_getenv(char *str_env, t_cmd *args)
{
	t_env	*current;
	size_t	len;
	size_t	len2;

	current = *args->env;
	len = ft_strlen(str_env);
	while (current)
	{
		len2 = ft_strlen(current->key);
		if (len2 == len && !ft_strncmp(current->key, str_env, len))
		{
			if (current->value)
				return (ft_strdup(current->value));
			else
				return (NULL);
		}
		current = current->next;
	}
	return (NULL);
}

t_env	**create_env(char **exp)
{
	t_env	**head;
	t_env	*temp;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	head = (t_env **)malloc(sizeof(t_env *));
	key = get_key(exp[i]);
	value = get_value(exp[i]);
	temp = env_newlst(key, value);
	*head = temp;
	i++;
	while (exp[i])
	{
		key = get_key(exp[i]);
		value = get_value(exp[i]);
		env_addback(head, env_newlst(key, value));
		i++;
	}
	return (head);
}

// char	*find_env(char *temp, t_cmd *args)
// {
// 	t_env	*current;
// 	int		i;
// 	char	*ret;

// 	current = *args->env;
// 	i = 0;
// 	while (current)
// 	{
// 		if (!ft_strncmp(temp, current->content, ft_strlen(temp)))
// 		{
// 			while (((char *)current->content)[i] != '=')
// 				i++;
// 			i++;
// 			ret = ft_strdup(((char *)current->content) + i);
// 			return (ret);
// 		}
// 		current = current->next;
// 	}
// 	return (NULL);
// }

void	my_env(t_cmd *args)
{
	t_env	*temp;

	temp = *args->env;
	while (temp)
	{
		if (temp->value)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

int	find_equal(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}
