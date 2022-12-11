/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 21:56:28 by aball             #+#    #+#             */
/*   Updated: 2022/12/11 13:28:59 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	flag_in2(t_pipe *t, t_cmd *args)
{
	char	*temp;

	t->in = 1;
	temp = ft_strdup(t->cmd[0] + 1);
	validate_path(temp, args);
	t->cmd = remove_str(t->cmd, 0);
	t->cmd = append_str(t->cmd, temp);
	free(temp);
	t->path = ft_strdup(args->path);
	my_free(args->path);
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
