/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 21:07:48 by aball             #+#    #+#             */
/*   Updated: 2022/12/12 03:06:39 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	flag_pipe(t_cmd *args)
{
	t_pipe	*temp;

	temp = *args->pipe;
	while (temp)
	{
		if (temp->cmd[0] && temp->cmd[0][0] == '|'
			&& !temp->double_q && !temp->single_q
				&& ft_strlen(temp->cmd[0]) == 1)
			temp->is_pipe = 1;
		temp = temp->next;
	}
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

void	flag_here_doc(t_cmd *args)
{
	t_pipe	*temp;
	t_pipe	*prev;
	int		i;

	i = 0;
	temp = *args->pipe;
	prev = NULL;
	args->heredoc_n = 0;
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
}

int	flag_list(t_cmd *args)
{
	t_pipe	*temp;

	flag_pipe(args);
	flag_out(args);
	flag_in(args);
	flag_here_doc(args);
	temp = *args->pipe;
	if (temp->is_pipe || lstlast_pipe(*args->pipe)->is_pipe)
	{
		*args->err = 258;
		lstclear_pipe(args->pipe, my_free);
		my_free(args->s);
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}
