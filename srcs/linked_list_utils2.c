/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 04:04:01 by aball             #+#    #+#             */
/*   Updated: 2022/12/16 03:13:05 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_args_back(t_cmd *args, int i)
{
	validate_path(args->cmd[i], args);
	lstadd_back_pipe(args->pipe, lstnew_pipe(args->cmd[i], args->path));
	my_free(args->path);
}

void	setup_lst_front(t_cmd *args, int i)
{
	args->pipe = (t_pipe **)malloc(sizeof(t_pipe *));
	validate_path(args->cmd[i], args);
}

t_pipe	*ret_pipe_location(t_pipe **head, int node)
{
	t_pipe	*temp;

	temp = *head;
	while (node && temp)
	{
		temp = temp->next;
		node--;
	}
	return (temp);
}

void	shuffle_it(char *str, int i)
{
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}

void	create_pipe_list(t_cmd *args)
{
	t_pipe	*temp;
	int		i;

	i = 0;
	setup_lst_front(args, i);
	temp = lstnew_pipe(args->cmd[i], args->path);
	my_free(args->path);
	*args->pipe = temp;
	temp->next = NULL;
	i++;
	while (args->cmd[i])
	{
		parse_args_back(args, i);
		i++;
		temp = temp->next;
	}
	remove_quotes(args->pipe, 0, 0);
}
