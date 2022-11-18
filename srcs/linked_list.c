/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:30:22 by aball             #+#    #+#             */
/*   Updated: 2022/11/17 18:07:43 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pipe	*lstnew_pipe(char *content, char *path)
{
	t_pipe	*new;

	new = (t_pipe *)malloc(sizeof(t_pipe));
	if (!new)
		return (0);
	new->cmd = (char **)malloc(sizeof(char *) * 2);
	new->cmd[0] = ft_strdup(content);
	new->cmd[1] = NULL;
	new->is_pipe = 0;
	new->path = path;
	new->next = NULL;
	return (new);
}

void	lstadd_back_pipe(t_pipe **lst, t_pipe *new)
{
	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		new->next = 0;
		return ;
	}
	lstlast_pipe(*lst)->next = new;
}

t_pipe	*lstlast_pipe(t_pipe *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lstclear_pipe(t_pipe **lst, void (*del)(void *))
{
	t_pipe	*clear;

	while (*lst)
	{
		clear = (*lst)->next;
		lstdelone_pipe(*lst, del);
		*lst = clear;
	}
}

void	lstdelone_pipe(t_pipe *lst, void (*del)(void *))
{
	if (lst)
	{
		freedom(lst->cmd);
		del(lst->path);
		del(lst);
	}
}

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
	if (count > 0)
		pre_pipe(head, count)->next = node2;
	node1->next = node2->next;
	node2->next = node1;
	if (count > 0)
		return ;
	*head = node2;
}