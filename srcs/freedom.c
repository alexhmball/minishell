/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:10:42 by aball             #+#    #+#             */
/*   Updated: 2022/12/09 21:51:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	freedom(char **free_me)
{
	int	i;

	i = 0;
	while (*free_me && free_me && free_me[i])
		my_free(free_me[i++]);
	my_free(free_me);
	free_me = NULL;
	return (1);
}

void	total_freedom(t_cmd *args)
{
	clear_env(args->env);
	my_free(args->env);
	my_free(args->s);
	rl_clear_history();
}

void	my_free(void *content)
{
	if (content)
	{
		free(content);
		content = NULL;
	}
	content = NULL;
}

void	executioner(t_cmd *args)
{
	total_freedom(args);
	lstclear_pipe(args->pipe, my_free);
	exit(*args->err);
}
