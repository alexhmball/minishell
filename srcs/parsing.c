/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:22:16 by aball             #+#    #+#             */
/*   Updated: 2022/12/10 21:53:48 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	move_here_doc(t_cmd *args)
{
	t_pipe	*temp;
	int		i;

	i = 0;
	temp = *args->pipe;
	while (temp)
	{
		if (temp->next && !temp->here_doc && temp->next->here_doc
			&& !temp->next->is_pipe && !temp->next->in && !temp->next->out)
		{
			swap_node(temp, temp->next, args->pipe, i);
			temp = *args->pipe;
			i = -1;
		}
		if (i > -1)
		{
			temp = temp->next;
		}
		i++;
	}
}

void	remove_pipes(t_cmd *args)
{
	t_pipe	*temp;
	t_pipe	*prev;
	int		i;

	i = 0;
	temp = *args->pipe;
	prev = NULL;
	while (temp)
	{
		if (temp->next && temp->is_pipe)
		{
			temp = remove_node(args->pipe, temp, prev, i);
			args->pipe_n++;
		}
		prev = temp;
		temp = temp->next;
		i++;
	}
}

int	parse_pipe(t_cmd *args)
{
	if (!flag_list(args))
		return (0);
	find_cmd_args(args);
	organize_cmds(args);
	remove_pipes(args);
	confirm_path(args);
	find_errors(args, args->pipe);
	return (1);
}

int	init_cmd(t_cmd *args)
{
	init_struct(args);
	args->s = readline("\x1b[30m\x1b[46mminishell$\x1b[m ");
	if (!args->s)
		return (0);
	if (args->s && *args->s)
		add_history(args->s);
	else
		return (1);
	args->cmd = quote_validator(args, 0, 0);
	if (!args->cmd)
	{
		printf("minishell: Error: invalid quotes\n");
		return (1);
	}
	return (5);
}

int	parsing(t_cmd *args)
{
	int		ret;

	ret = init_cmd(args);
	if (ret == 0)
		return (0);
	if (ret == 1)
		return (1);
	create_pipe_list(args);
	if (!parse_pipe(args))
		return (*args->err);
	freedom(args->cmd);
	if (!args->pipe_n)
		us_not_printing(args);
	pipex(args);
	lstclear_pipe(args->pipe, my_free);
	my_free(args->s);
	return (1);
}
