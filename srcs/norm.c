/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 03:25:50 by ballzball         #+#    #+#             */
/*   Updated: 2022/12/16 03:28:10 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_redir(t_cmd *args)
{
	t_pipe	*temp;

	temp = *args->pipe;
	while (temp->next)
	{
		if (is_redir(temp->cmd[0][0]) && is_redir(temp->next->cmd[0][0]))
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	expand_it(t_cmd *args)
{
	t_pipe	*temp;

	temp = *args->pipe;
	while (temp)
	{
		if (!temp->here_doc)
			find_expand(temp, 0, 0, args);
		strip_tease(temp, args);
		temp = temp->next;
	}
}

void	error_message_token(t_cmd *args)
{
	*args->err = 258;
	lstclear_pipe(args->pipe, my_free);
	my_free(args->s);
	freedom(args->cmd);
	printf("minishell: syntax error remove extra token\n");
}

int	flag_list(t_cmd *args)
{
	t_pipe	*temp;
	int		flag1;
	int		flag2;
	int		flag3;

	flag1 = 1;
	flag2 = 1;
	flag3 = 1;
	if (!check_redir(args))
	{
		flag1 = flag_pipe(args);
		flag2 = flag_out(args);
		flag_in(args);
		flag3 = flag_here_doc(args);
	}
	temp = *args->pipe;
	if (temp->is_pipe || lstlast_pipe(*args->pipe)->is_pipe
		|| flag1 || flag2 || flag3)
	{
		error_message_token(args);
		return (0);
	}
	expand_it(args);
	return (1);
}
