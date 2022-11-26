/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 04:04:01 by aball             #+#    #+#             */
/*   Updated: 2022/11/27 03:26:07 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_args_back(t_cmd *args, int i)
{
	// my_free(args->path);
	validate_path(args->cmd[i], args);
	args->cmd[i] = check_single_path(args->cmd[i], args);
	lstadd_back_pipe(args->pipe, lstnew_pipe(args->cmd[i], args->path));
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
	// printf("cmd: %s\n", cmd_pipe->cmd[0]);
	arg_pipe = ret_pipe_location(args->pipe, arg);
	// printf("arg: %s\n", arg_pipe->cmd[0]);
	// printf("pre: %s\n", pre_pipe(args->pipe, arg)->next->cmd[0]);
	while (arg_pipe->cmd[i])
		cmd_pipe->cmd = append_str(cmd_pipe->cmd, arg_pipe->cmd[i++]);
	remove_node(args->pipe, arg_pipe, pre_pipe(args->pipe, arg)->next, arg);
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
			if (temp->path && !temp->in && !temp->out && arg == -1 && !temp->is_pipe)
				cmd = counter;
			else if (!temp->in && !temp->out && cmd != -1 && !temp->is_pipe)
				arg = counter;
			else if (temp->is_pipe)
				pipe = 0;
			counter++;
			temp = temp->next;
		}
		if (cmd != -1 && arg != -1)
		{
			// printf("cmd: %d arg: %d\n", cmd, arg);
			group_args(args, arg, cmd);
			counter = 0;
			temp = *args->pipe;
		}
		pipe = 1;
		arg = -1;
		cmd = -1;
	}
}

void	create_pipe_list(t_cmd *args)
{
	t_pipe	*temp;
	int		i;

	i = 0;
	setup_lst_front(args, i);
	temp = lstnew_pipe(args->cmd[i], args->path);
	if (args->cmd[i][0] == '>' || args->cmd[i][0] == '<')
	{
		i++;
		temp->cmd = append_str(temp->cmd, args->cmd[i]);
	}
	my_free(args->path);
	*args->pipe = temp;
	temp->next = NULL;
	i++;
	while (args->cmd[i])
	{
		if (validate_path(args->cmd[i], args) && args->cmd[i - 1][0] != '>' && args->cmd[i - 1][0] != '<' && !temp->path)
		{
			args->cmd[i] = check_single_path(args->cmd[i], args);
			lstadd_back_pipe(args->pipe, lstnew_pipe(args->cmd[i], args->path));
			// my_free(args->path);
			temp = temp->next;
		}
		else if (args->cmd[i] && args->cmd[i][0] == '|')
		{
			parse_args_back(args, i);
			temp = temp->next;
			temp->is_pipe = 1;
		}
		else if (args->cmd[i] && (args->cmd[i][0] == '>' || args->cmd[i][0] == '<'))
		{
			parse_args_back(args, i);
			temp = temp->next;
			i++;
			if (args->cmd[i])
				temp->cmd = append_str(temp->cmd, args->cmd[i]);
		}
		else if (args->cmd[i] && temp->cmd[0][0] != '>' && temp->cmd[0][0] != '<')
			temp->cmd = append_str(temp->cmd, args->cmd[i]);
		else
		{
			validate_path(args->cmd[i], args);
			args->cmd[i] = check_single_path(args->cmd[i], args);
			lstadd_back_pipe(args->pipe, lstnew_pipe(args->cmd[i], args->path));
			// my_free(args->path);
			temp = temp->next;
		}
		i++;
	}
}