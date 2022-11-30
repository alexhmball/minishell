/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desperation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 01:42:34 by aball             #+#    #+#             */
/*   Updated: 2022/12/01 01:52:46 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	insert_sleep(t_pipe *node)
{
	t_pipe	*next;
	t_pipe	*new;

	next = node->next;
	new = lstnew_pipe("sleep", "/bin/sleep");
	new->cmd = append_str(new->cmd, "0");
	new->next = next;
	node->next = new;
}

void	desperation(t_cmd *args)
{
	t_pipe	*node;

	node = *args->pipe;
	while (node)
	{
		if (node->here_doc)
			insert_sleep(node);
		node = node->next;
	}
}