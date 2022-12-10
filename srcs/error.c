/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 23:22:03 by aball             #+#    #+#             */
/*   Updated: 2022/12/10 22:01:48 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_error(t_cmd *args, int code)
{
	if (code == 13)
		*args->err = 126;
	if (code == 2)
		*args->err = 127;
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
