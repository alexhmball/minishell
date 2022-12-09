/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:53:03 by aball             #+#    #+#             */
/*   Updated: 2022/12/09 17:02:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*remove_env(t_list **head, t_list *node, t_list *prev_node, int c)
{
	if (c == 0)
		*head = node->next;
	else
		prev_node->next = node->next;
	node->next = NULL;
	ft_lstdelone(node, my_free);
	return (*head);
}

void	my_unset(t_cmd *args, t_pipe *node)
{
	t_list	*current;
	t_list	*temp;
	size_t	len;
	int		i;

	current = *args->env;
	temp = current;
	i = 0;
	if (two_d_strlen(node->cmd) > 1)
	{
		while (current)
		{
			len = find_equal(current->content);
			if (len >= ft_strlen(node->cmd[1])
				&& !ft_strncmp(current->content, node->cmd[1], len))
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
