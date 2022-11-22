/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:10:42 by aball             #+#    #+#             */
/*   Updated: 2022/11/22 18:54:27 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	freedom(char **free_me)
{
	int	i;

	i = 0;
	while (free_me && free_me[i])
		my_free(free_me[i++]);
	my_free(free_me);
	free_me = NULL;
	return (1);
}

void	total_freedom(t_cmd *args)
{
	ft_lstclear(args->env, my_free);
	my_free(args->env);
	my_free(args->s);
	freedom(args->cmd);
	my_free(args->expand);
	rl_clear_history();
}

void	my_free(void *content)
{
	if (content)
	{
		free(content);
		content = NULL;
	}
}
