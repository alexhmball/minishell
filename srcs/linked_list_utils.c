/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:33:53 by aball             #+#    #+#             */
/*   Updated: 2022/11/22 22:58:40 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pipe	*pre_pipe(t_pipe **head, int count)
{
	t_pipe	*temp;
	int		i;

	temp = *head;
	i = 0;
	while(temp->next && i < count)
	{
		temp = temp->next;
		i++;
	}
	return (temp);
}

void	swap_node(t_pipe *node1, t_pipe *node2, t_pipe **head, int count)
{
	if (count == 0)
		*head = node2;
	if (count > 0)
		pre_pipe(head, count)->next = node2;
	node1->next = node2->next;
	node2->next = node1;
}

void	organize_cmds(t_cmd *args)
{
	t_pipe	*temp;
	int		c;

	temp = *args->pipe;
	c = 0;
	while (temp)
	{
		if (temp->next && temp->next->in && temp->path)
			swap_node(temp, temp->next, args->pipe, c);
		if (temp->next && temp->out && temp->next->path)
			swap_node(temp, temp->next, args->pipe, c);
		c++;
		temp = temp->next;
	}
}

t_pipe	*remove_node(t_pipe **head, t_pipe *node, t_pipe *prev_node)
{

	if (node == *head)
		*head = node->next;
	else
		prev_node->next = node->next;
	lstdelone_pipe(node, my_free);
	return (*head);
}

void	flag_list(t_cmd *args)
{
	t_pipe	*temp;

	temp = *args->pipe;
	while (temp)
	{
		if (temp->cmd[0][0] == '<')
		{
			temp->in = 1;
			temp->cmd = remove_str(temp->cmd, 0);
		}
		else if (temp->cmd[0][0] == '>')
		{
			temp->out = 1;
			temp->cmd = remove_str(temp->cmd, 0);
		}
		if (temp->next && temp->next->is_pipe)
			temp = remove_node(args->pipe, temp->next, temp);
		temp = temp->next;
	}
}
