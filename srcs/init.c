/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:50:17 by ballzball         #+#    #+#             */
/*   Updated: 2022/12/10 21:55:09 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_struct(t_cmd *args)
{
	args->path = NULL;
	args->cmd = NULL;
	args->s = NULL;
	args->pipe_n = 0;
	args->heredoc_n = 0;
	args->flag = 0;
}

void	init_all(t_cmd *args)
{
	args->err = 0;
	args->env = NULL;
	args->path = NULL;
	args->cmd = NULL;
	args->s = NULL;
}
