/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 04:04:01 by aball             #+#    #+#             */
/*   Updated: 2022/11/30 01:11:52 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_args_back(t_cmd *args, int i)
{
	validate_path(args->cmd[i], args);
	// args->cmd[i] = check_single_path(args->cmd[i], args);
	lstadd_back_pipe(args->pipe, lstnew_pipe(args->cmd[i], args->path));
	my_free(args->path);
}

void	setup_lst_front(t_cmd *args, int i)
{
	args->pipe = (t_pipe **)malloc(sizeof(t_pipe *));
	// my_free(args->path);
	validate_path(args->cmd[i], args);
	// args->cmd[i] = check_single_path(args->cmd[i], args);

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

void	group_args(t_cmd *args, int arg, int cmd)
{
	t_pipe	*cmd_pipe;
	t_pipe	*arg_pipe;
	int		i;

	i = 0;
	cmd_pipe = ret_pipe_location(args->pipe, cmd);
	arg_pipe = ret_pipe_location(args->pipe, arg);
	while (arg_pipe->cmd[i])
		cmd_pipe->cmd = append_str(cmd_pipe->cmd, arg_pipe->cmd[i++]);
	remove_node(args->pipe, arg_pipe, ret_pipe_location(args->pipe, arg - 1), arg);
}

void	find_cmd_args(t_cmd *args)
{
	t_pipe	*temp;
	int		cmd;
	int		arg;
	int		counter;
	int		pipe;

	temp = *args->pipe;
	cmd = -1;
	counter = 0;
	pipe = 1;
	arg = -1;
	while (temp)
	{
		while (pipe && temp)
		{
			if (temp->path && !temp->in && !temp->out && arg == -1 && !temp->is_pipe && cmd == -1)
				cmd = counter;
			else if (!temp->in && !temp->out && cmd != -1  && arg == -1 && !temp->is_pipe)
				arg = counter;
			else if (temp->is_pipe)
				pipe = 0;
			counter++;
			temp = temp->next;
		}
		if (cmd != -1 && arg != -1)
		{
			group_args(args, arg, cmd);
			counter = 0;
			temp = *args->pipe;
		}
		pipe = 1;
		arg = -1;
		cmd = -1;
	}
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
	t_pipe	*prev;
	int		i;

	i = 0;
	setup_lst_front(args, i);
	temp = lstnew_pipe(args->cmd[i], args->path);
	my_free(args->path);
	*args->pipe = temp;
	temp->next = NULL;
	prev = NULL;
	i++;
	while (args->cmd[i])
	{
		parse_args_back(args, i);
		i++;
		temp = temp->next;
	}
	// print_pipe(args->pipe);
	remove_quotes(args->pipe, 0, 0);
	print_pipe(args->pipe);
	temp = *args->pipe;
	i = 0;
	while (temp)
	{
		if (temp->cmd[0][0] == '|' && !temp->double_q && !temp->single_q)
			temp->is_pipe = 1;
		else if (temp->cmd[0][0] == '<' && ft_strlen(temp->cmd[0]) == 1)
		{
			temp->next->in = 1;
			temp = remove_node(args->pipe, temp, prev, i);
			i = 0;
		}
		else if (temp->cmd[0][0] == '>' && ft_strlen(temp->cmd[0]) == 1)
		{
			temp->next->out = 1;
			temp = remove_node(args->pipe, temp, prev, i);
			i = 0;
		}
		else if (temp->cmd[0][0] == '<' && temp->cmd[0][1] != '<' && !temp->double_q && !temp->single_q)
		{
			temp->in = 1;
			temp->cmd[0] = ft_strdup(temp->cmd[0] + 1);
		}
		else if (temp->cmd[0][0] == '<' && ft_strlen(temp->cmd[0]) > 1 && temp->cmd[0][1] != '<' && !temp->double_q && !temp->single_q)
			temp->here_doc = 1;
		else if (temp->cmd[0][0] == '>' && temp->cmd[0][1] != '>' && !temp->double_q && !temp->single_q)
		{
			temp->out = 1;
			temp->cmd[0] = ft_strdup(temp->cmd[0] + 1);
		}
		else if (temp->cmd[0][0] == '>' && temp->cmd[0][1] == '>' && !temp->double_q && !temp->single_q)
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
		prev = temp;
		temp = temp->next;
		i++;
	}
}
