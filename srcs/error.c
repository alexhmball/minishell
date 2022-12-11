/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 23:22:03 by aball             #+#    #+#             */
/*   Updated: 2022/12/11 14:05:16 by ballzball        ###   ########.fr       */
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
		else
			*args->err = 0;
		temp = temp->next;
	}
}
