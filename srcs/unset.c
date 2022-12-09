/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:53:03 by aball             #+#    #+#             */
/*   Updated: 2022/12/09 22:05:06 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*remove_env(t_env **head, t_env *node, t_env *prev_node, int c)
{
	if (c == 0)
		*head = node->next;
	else
		prev_node->next = node->next;
	node->next = NULL;
	env_delone(node);
	return (*head);
}

void	my_unset(t_cmd *args, t_pipe *node)
{
	t_env	*current;
	t_env	*temp;
	size_t	len;
	int		i;

	current = *args->env;
	temp = current;
	i = 0;
	if (two_d_strlen(node->cmd) > 1)
	{
		while (current)
		{
			len = ft_strlen(current->key);
			if (len == ft_strlen(node->cmd[1])
				&& !ft_strncmp(current->key, node->cmd[1], len))
			{
				current = remove_env(args->env, current, temp, i);
				i = 0;
			}
			temp = current;
			current = current->next;
			i++;
		}
	}
}
