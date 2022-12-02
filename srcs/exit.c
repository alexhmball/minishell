/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:16:28 by aball             #+#    #+#             */
/*   Updated: 2022/12/03 01:21:30 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_shell(t_cmd *args, t_pipe *node)
{
	if (two_d_strlen(node->cmd) > 1)
	{
		perror("minishell: exit");
		args->err = 255;
	}
	exit(args->err);
}