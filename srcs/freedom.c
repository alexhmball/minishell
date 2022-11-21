/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:10:42 by aball             #+#    #+#             */
/*   Updated: 2022/11/21 10:58:54 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	freedom(char **free_me)
{
	int	i;

	i = 0;
	while (free_me && free_me[i])
		free(free_me[i++]);
	free(free_me);
	free_me = NULL;
}

void	total_freedom(t_cmd *args)
{
	ft_lstclear(args->env, free);
	free(args->env);
	free(args->s);
	freedom(args->cmd);
	free(args->expand);
	// free(args);
	rl_clear_history();
}

void	my_free(void *content)
{
	free(content);
	content = NULL;
}
