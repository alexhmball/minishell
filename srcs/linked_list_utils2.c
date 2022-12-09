/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 04:04:01 by aball             #+#    #+#             */
/*   Updated: 2022/12/09 20:48:38 by codespace        ###   ########.fr       */
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

void	print_pipe(t_pipe **head)
{
	t_pipe	*temp;
	int		i;

	temp = *head;
	while (temp)
	{
		i = 0;
		while (temp->cmd[i])
		{
			printf("cmd: %s\n", temp->cmd[i++]);
		}
		printf("path: %s\n", temp->path);
		printf("pipe? %d\n", temp->is_pipe);
		printf("in? %d\n", temp->in);
		printf("out? %d\n", temp->out);
		printf("single? %d\n", temp->single_q);
		printf("double? %d\n", temp->double_q);
		printf("append? %d\n", temp->append);
		printf("heredoc? %d\n", temp->here_doc);
		printf(".....\n");
		temp = temp->next;
	}
	printf("...~~~~~~~~~~~~~~..\n");
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
	remove_quotes(args->pipe, 0, 0, args);
	// freedom(args->cmd);
}
