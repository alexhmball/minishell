/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 23:22:03 by aball             #+#    #+#             */
/*   Updated: 2022/12/16 15:19:43 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_error(int code)
{
	if (code == 13)
		g_error = 126;
	if (code == 2)
		g_error = 127;
}

void	find_errors(t_cmd *args, t_pipe **head)
{
	t_pipe	*temp;

	temp = *head;
	while (temp)
	{
		if (!temp->out && !temp->in && !temp->is_pipe && !temp->here_doc
			&& !temp->path && !is_us(temp))
			*args->err = 127;
		else if (temp->path &&!temp->out && !temp->in && !temp->is_pipe
			&& !temp->here_doc && access(temp->path, X_OK) == -1 && !is_us(temp)
			&& access(temp->path, R_OK) == -1)
			*args->err = 126;
		else if (ft_strncmp(temp->cmd[0], "exit", 4))
			*args->err = 0;
		temp = temp->next;
	}
}

void	print_access(t_pipe *cmd, char *error)
{
	set_error(errno);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->cmd[0], 2);
	ft_putstr_fd(error, 2);
}
