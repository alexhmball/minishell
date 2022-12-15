/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:17:57 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/15 22:05:01 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_pipes(t_cmd *args)
{
	t_pipe	*temp;
	pid_t	child;
	int		fd[2];
	int		counter;

	temp = *args->pipe;
	counter = 0;
	while (temp)
	{
		child = fork();
		if (!child)
		{
		}
		counter++;
		temp = temp->next;
	}
	return ;
}