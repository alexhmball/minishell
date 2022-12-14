/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:53:03 by aball             #+#    #+#             */
/*   Updated: 2022/12/14 21:01:32 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*remove_env(t_env **head, t_env *node, t_env *prev_node, int c)
{
	if (!node)
		return (NULL);
	if (c == 0)
		*head = node->next;
	else
		prev_node->next = node->next;
	node->next = NULL;
	env_delone(node);
	return (*head);
}

static void	check_unset(t_cmd *args, t_pipe *node, t_env *current, int j)
{
	size_t	len;
	size_t	i;
	t_env	*temp;

	i = 0;
	temp = current;
	while (current)
	{
		len = ft_strlen(current->key);
		if (len == ft_strlen(node->cmd[j])
			&& !ft_strncmp(current->key, node->cmd[j], len))
		{
			current = remove_env(args->env, current, temp, i);
			if (!current)
				break ;
			i = -1;
		}
		temp = current;
		current = current->next;
		i++;
	}
}

void	my_unset(t_cmd *args, t_pipe *node)
{
	t_env	*current;
	size_t	j;

	j = 1;
	while (node->cmd[j])
	{
		current = *args->env;
		check_unset(args, node, current, j);
		j++;
	}
	args->env_for_excecute = make_env_for_ex(args->env, args->env_for_excecute);
}
