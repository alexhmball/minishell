/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:10:42 by aball             #+#    #+#             */
/*   Updated: 2022/11/12 20:58:02 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	freedom(char **free_me)
{
	int	i;

	i = 0;
	while (free_me[i])
		free(free_me[i++]);
	free(free_me);
}

void	total_freedom(t_cmd *args)
{
	ft_lstclear(args->env, free);
	free(args->env);
	free(args->s);
	freedom(args->cmd);
	free(args->expand);
	rl_clear_history();
}
