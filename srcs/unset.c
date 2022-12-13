/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:53:03 by aball             #+#    #+#             */
/*   Updated: 2022/12/13 16:38:31 by ballzball        ###   ########.fr       */
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

void	my_unset(t_cmd *args, t_pipe *node)
{
	t_env	*current;
	t_env	*temp;
	size_t	len;
	size_t	i;
	size_t	j;

	j = 1;
	while (node->cmd[j])
	{
		i = 0;
		current = *args->env;
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
		j++;
	}
	args->env_for_excecute = make_env_for_ex(args->env, args->env_for_excecute);
}
