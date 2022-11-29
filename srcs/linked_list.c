/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:30:22 by aball             #+#    #+#             */
/*   Updated: 2022/11/29 21:13:02 by aball            ###   ########.fr       */
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
	new->double_q = 0;
	new->single_q = 0;
	new->in = 0;
	new->out = 0;
	new->path = ft_strdup(path);
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
		new->next = NULL;
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
	del(lst);
}

void	lstdelone_pipe(t_pipe *lst, void (*del)(void *))
{
	if (lst)
	{
		if (lst->path)
			del(lst->path);
		if (lst->cmd)
			freedom(lst->cmd);
		if (lst)
			del(lst);
	}
}
