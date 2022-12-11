/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 02:55:27 by aball             #+#    #+#             */
/*   Updated: 2022/12/12 03:06:18 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_size(t_env **head)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = *head;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

char	**make_env_for_ex(t_env **head, char **free_me)
{
	t_env	*temp;
	char	**env;
	char	*str;
	int		i;

	i = 0;
	temp = *head;
	env = (char **)malloc(sizeof(char *) * (env_size(head) + 1));
	if (!env)
		return (NULL);
	while (temp)
	{
		if (temp->value)
		{
			str = ft_strjoin(temp->key, "=");
			env[i++] = ft_strjoin(str, temp->value);
			free(str);
		}
		else
			env[i++] = ft_strdup(temp->key);
		temp = temp->next;
	}
	env[i] = NULL;
	freedom(free_me);
	return (env);
}

char	**twd_d_strdup(char **str)
{
	char	**new;
	int		i;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (two_d_strlen(str) + 1));
	while (str[i])
	{
		new[i] = ft_strdup(str[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}
