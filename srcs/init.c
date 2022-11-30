/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:50:17 by ballzball         #+#    #+#             */
/*   Updated: 2022/11/30 22:31:26 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_struct(t_cmd *args)
{
	args->path = NULL;
	args->cmd = NULL;
	args->s = NULL;
}

void	init_all(t_cmd *args)
{
	args->err = 0;
	args->env = NULL;
	args->path = NULL;
	args->cmd = NULL;
	args->s = NULL;
	args->fd = 0;
}