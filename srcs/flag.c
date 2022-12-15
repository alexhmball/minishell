/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 21:07:48 by aball             #+#    #+#             */
/*   Updated: 2022/12/16 03:03:03 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	flag_pipe(t_cmd *args)
{
	t_pipe	*temp;

	temp = *args->pipe;
	while (temp)
	{
		if (temp->cmd[0] && temp->cmd[0][0] == '|'
			&& !temp->double_q && !temp->single_q
				&& ft_strlen(temp->cmd[0]) == 1)
			temp->is_pipe = 1;
		if (ft_strlen(temp->cmd[0]) > 1 && temp->cmd[0][0] == '|'
			&& !temp->double_q && !temp->single_q)
			return (1);
		temp = temp->next;
	}
	return (0);
}

static t_pipe	*here_doc_2(t_pipe *temp, t_pipe *prev, int *i, t_cmd *args)
{
	char	*str;

	if (ft_strlen(temp->cmd[0]) == 2 && temp->next)
	{
		temp->next->here_doc = 1;
		temp = remove_node(args->pipe, temp, prev, *i);
		*i = 0;
	}
	else if (ft_strlen(temp->cmd[0]) > 2)
	{
		temp->here_doc = 1;
		str = ft_strdup(temp->cmd[0] + 2);
		freedom(temp->cmd);
		temp->cmd = (char **)malloc(sizeof(char *) * 2);
		temp->cmd[0] = ft_strdup(str);
		temp->cmd[1] = NULL;
		free(str);
	}
	args->heredoc_n++;
	return (temp);
}

int	flag_here_doc(t_cmd *args)
{
	t_pipe	*temp;
	t_pipe	*prev;
	int		i;

	i = 0;
	temp = *args->pipe;
	prev = NULL;
	args->heredoc_n = 0;
	if (check_doubles(args))
		return (1);
	while (temp)
	{
		if (temp->cmd[0] && temp->cmd[0][0] == '<'
				&& ft_strlen(temp->cmd[0]) > 1 && temp->cmd[0][1] == '<'
					&& !temp->double_q && !temp->single_q)
			temp = here_doc_2(temp, prev, &i, args);
		prev = temp;
		temp = temp->next;
		i++;
	}
	return (0);
}

int	is_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}
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
		*args->err = 258;
		lstclear_pipe(args->pipe, my_free);
		my_free(args->s);
		freedom(args->cmd);
		printf("minishell: syntax error remove extra token\n");
		return (0);
	}
	temp = *args->pipe;
	while (temp)
	{
		if (!temp->here_doc)
			find_expand(temp, 0, 0, args);
		strip_tease(temp, args);
		temp = temp->next;
	}
	return (1);
}
