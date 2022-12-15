/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 04:04:01 by aball             #+#    #+#             */
/*   Updated: 2022/12/15 22:13:24 by ballzball        ###   ########.fr       */
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

void	shuffle_it(char *str, int i)
{
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}

void	strip_tease(t_pipe *node, t_cmd *args)
{
	size_t	i;
	
	i = 0;
	while (*node->cmd && node->cmd[0][i])
	{
		if (node->cmd[0][i] == 1 || node->cmd[0][i] == 2)
			shuffle_it(node->cmd[0], i);
		else
			i++;
			
	}
	if (node->expand)
		node->cmd = ft_split(node->cmd[0], ' ');
	validate_path(node->cmd[0], args);
	if (args->path)
	{
		node->path = ft_strdup(args->path);
		my_free(args->path);
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
	temp = *args->pipe;
	while (temp)
	{
		find_expand(temp, 0, 0, args);
		strip_tease(temp, args);
		temp = temp->next;
	}
}
