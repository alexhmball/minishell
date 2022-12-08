/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 21:56:28 by aball             #+#    #+#             */
/*   Updated: 2022/12/08 22:44:56 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	flag_in2(t_pipe *t, t_cmd *args)
{
	t->in = 1;
	t->cmd[0] = ft_strdup(t->cmd[0] + 1);
	validate_path(t->cmd[0], args);
	t->path = ft_strdup(args->path);
}

void	flag_in(t_cmd *args)
{
	t_pipe	*t;
	t_pipe	*prev;
	int		i;

	t = *args->pipe;
	prev = NULL;
	i = 0;
	while (t)
	{
		if (t->cmd[0] && t->cmd[0][0] == '<' && ft_strlen(t->cmd[0]) == 1)
		{
			t->next->in = 1;
			t = remove_node(args->pipe, t, prev, i);
			i = 0;
		}
		else if (t->cmd[0] && t->cmd[0][0] == '<'
		&& t->cmd[0][1] != '<' && !t->double_q && !t->single_q)
			flag_in2(t, args);
		prev = t;
		t = t->next;
		i++;
	}
}
