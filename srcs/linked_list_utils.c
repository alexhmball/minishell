/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:33:53 by aball             #+#    #+#             */
/*   Updated: 2022/11/29 18:41:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pipe	*pre_pipe(t_pipe **head, int count)
{
	t_pipe	*temp;
	int		i;

	temp = *head;
	i = 0;
	count -= 2;
	while(i < count)
	{
		temp = temp->next;
		i++;
	}
	return (temp);
}

void	swap_node(t_pipe *node1, t_pipe *node2, t_pipe **head, int c)
{
	if (c == 0)
		*head = node2;
	else
		ret_pipe_location(head, c - 1)->next = node2;
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
		if (temp->next && temp->in && !temp->next->in && !temp->next->out
			&& !temp->is_pipe && !temp->next->is_pipe)
		{
			swap_node(temp, temp->next, args->pipe, c);
			temp = *args->pipe;
			c = -1;
		}
		if (c > -1)
		{
			temp = temp->next;
		}
		c++;
	}
	temp = *args->pipe;
	c = 0;
	while (temp)
	{
		if (temp->next != NULL && temp->out == 1 && temp->next->out == 0
			&& temp->is_pipe == 0 && temp->next->is_pipe == 0)
		{
			swap_node(temp, temp->next, args->pipe, c);
			temp = *args->pipe;
			c = -1;
		}
		if (c > -1)
		{
			temp = temp->next;
		}
		c++;
	}
}

t_pipe	*remove_node(t_pipe **head, t_pipe *node, t_pipe *prev_node, int c)
{

	if (c == 0)
		*head = node->next;
	else
		prev_node->next = node->next;
	node->next = NULL;
	lstdelone_pipe(node, my_free);
	return (*head);
}

int	flag_list(t_cmd *args)
{
	t_pipe	*temp;

	temp = *args->pipe;
	if (temp->cmd[0][0] == '|' || lstlast_pipe(*args->pipe)->is_pipe)
	{
		args->err = 258;
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}
