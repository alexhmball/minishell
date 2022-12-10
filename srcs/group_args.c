/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 22:43:38 by aball             #+#    #+#             */
/*   Updated: 2022/12/10 19:16:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	group_args(t_cmd *args, int arg, int cmd)
{
	t_pipe	*cmd_pipe;
	t_pipe	*arg_pipe;
	int		i;

	i = 0;
	cmd_pipe = ret_pipe_location(args->pipe, cmd);
	arg_pipe = ret_pipe_location(args->pipe, arg);
	while (arg_pipe->cmd[i])
		cmd_pipe->cmd = append_str(cmd_pipe->cmd, arg_pipe->cmd[i++]);
	remove_node(args->pipe, arg_pipe,
		ret_pipe_location(args->pipe, arg - 1), arg);
}

static t_pipe	*flag_args(t_pipe *temp, int *counter, int *cmd, int *arg)
{
	int	pipe;

	pipe = 1;
	while (pipe && temp)
	{
		if (!temp->in && !temp->out && !temp->here_doc
			&& *arg == -1 && !temp->is_pipe && *cmd == -1)
			*cmd = *counter;
		else if (!temp->in && !temp->out && !temp->here_doc
			&& *cmd != -1 && *arg == -1 && !temp->is_pipe)
			*arg = *counter;
		else if (temp->is_pipe)
			pipe = 0;
		*counter += 1;
		temp = temp->next;
	}
	return (temp);
}

void	find_cmd_args(t_cmd *args)
{
	t_pipe	*temp;
	int		cmd;
	int		arg;
	int		counter;

	temp = *args->pipe;
	cmd = -1;
	counter = 0;
	arg = -1;
	while (temp)
	{
		temp = flag_args(temp, &counter, &cmd, &arg);
		if (cmd != -1 && arg != -1)
		{
			group_args(args, arg, cmd);
			counter = 0;
			temp = *args->pipe;
		}
		arg = -1;
		cmd = -1;
	}
}
