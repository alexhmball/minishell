/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:50:17 by ballzball         #+#    #+#             */
/*   Updated: 2022/11/17 18:51:41 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_struct(t_cmd *args)
{
	args->path = NULL;
	args->cmd = NULL;
	args->s = NULL;
	args->expand = NULL;
}