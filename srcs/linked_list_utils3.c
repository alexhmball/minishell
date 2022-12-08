/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:19:18 by aball             #+#    #+#             */
/*   Updated: 2022/12/08 19:19:34 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	flag_list(t_cmd *args)
{
	t_pipe	*temp;

	temp = *args->pipe;
	if (temp->is_pipe || lstlast_pipe(*args->pipe)->is_pipe)
	{
		*args->err = 258;
		lstclear_pipe(args->pipe, my_free);
		my_free(args->s);
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}
