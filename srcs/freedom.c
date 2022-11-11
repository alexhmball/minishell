/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:10:42 by aball             #+#    #+#             */
/*   Updated: 2022/11/12 01:56:36 by ballzball        ###   ########.fr       */
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
