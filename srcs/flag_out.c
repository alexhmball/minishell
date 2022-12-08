/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_out.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 21:57:01 by aball             #+#    #+#             */
/*   Updated: 2022/12/08 21:57:07 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	flag_out_2(t_pipe *temp, t_pipe *prev, int i, t_cmd *args)
{
	temp->append = 1;
	temp->out = 1;
	if (ft_strlen(temp->cmd[0]) > 2)
		temp->cmd[0] = ft_strdup(temp->cmd[0] + 2);
	else
	{
		temp->next->out = 1;
		temp->next->append = 1;
		temp = remove_node(args->pipe, temp, prev, i);
	}
}

static void	flag_out_1(t_pipe *temp, t_pipe *prev, int *i, t_cmd *args)
{
	temp->next->out = 1;
	temp = remove_node(args->pipe, temp, prev, *i);
	*i = 0;
}

void	flag_out(t_cmd *args)
{
	t_pipe	*temp;
	t_pipe	*prev;
	int		i;

	i = 0;
	prev = NULL;
	temp = *args->pipe;
	while (temp)
	{
		if (temp->cmd[0] && temp->cmd[0][0] == '>'
				&& ft_strlen(temp->cmd[0]) == 1)
			flag_out_1(temp, prev, &i, args);
		else if (temp->cmd[0] && temp->cmd[0][0] == '>'
				&& temp->cmd[0][1] != '>' && !temp->double_q && !temp->single_q)
		{
			temp->out = 1;
			temp->cmd[0] = ft_strdup(temp->cmd[0] + 1);
		}
		else if (temp->cmd[0] && temp->cmd[0][0] == '>'
			&& temp->cmd[0][1] == '>' && !temp->double_q && !temp->single_q)
			flag_out_2(temp, prev, i, args);
		prev = temp;
		temp = temp->next;
		i++;
	}
}
