/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 04:04:01 by aball             #+#    #+#             */
/*   Updated: 2022/11/24 16:17:13 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_args_back(t_cmd *args, int i)
{
	my_free(args->path);
	validate_path(args->cmd[i], args);
	args->cmd[i] = check_single_path(args->cmd[i], args);
	lstadd_back_pipe(args->pipe, lstnew_pipe(args->cmd[i], args->path));
}

void	setup_lst_front(t_cmd *args, int i)
{
	args->pipe = (t_pipe **)malloc(sizeof(t_pipe *));
	my_free(args->path);
	validate_path(args->cmd[i], args);
	args->cmd[i] = check_single_path(args->cmd[i], args);

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
		if (validate_path(args->cmd[i], args) && args->cmd[i - 1][0] != '>' && args->cmd[i - 1][0] != '<')
		{
			args->cmd[i] = check_single_path(args->cmd[i], args);
			lstadd_back_pipe(args->pipe, lstnew_pipe(args->cmd[i], args->path));
			my_free(args->path);
			temp = temp->next;
			i++;
			while (args->cmd[i] && args->cmd[i][0] != '>' && args->cmd[i][0] != '<' && args->cmd[i][0] != '|')
			{
				temp->cmd = append_str(temp->cmd, args->cmd[i]);
				i++;
			}
		}
		else if (args->cmd[i][0] == '|')
		{
			parse_args_back(args, i);
			temp = temp->next;
			temp->is_pipe = 1;
		}
		else if (args->cmd[i][0] == '>' || args->cmd[i][0] == '<')
		{
			parse_args_back(args, i);
			temp = temp->next;
		}
		else
			temp->cmd = append_str(temp->cmd, args->cmd[i]);
		if (args->cmd[i])
			i++;
	}
}