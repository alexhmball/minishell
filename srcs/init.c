/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:50:17 by ballzball         #+#    #+#             */
/*   Updated: 2022/12/08 19:21:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_struct(t_cmd *args)
{
	args->path = NULL;
	args->cmd = NULL;
	args->s = NULL;
	args->pipe_n = 0;
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

// function that simulates heredoc like in bash
