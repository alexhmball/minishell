/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lowering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 05:13:38 by ballzball         #+#    #+#             */
/*   Updated: 2022/12/14 20:53:48 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_strtolower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
}

void	make_lower(t_cmd *args)
{
	t_pipe	*temp;

	temp = *args->pipe;
	while (temp)
	{
		if (temp->cmd && !temp->is_pipe && !temp->here_doc
			&& !temp->in && !temp->out)
		{
			ft_strtolower(temp->cmd[0]);
			if (!temp->path)
			{
				validate_path(temp->cmd[0], args);
				temp->path = ft_strdup(args->path);
				my_free(args->path);
			}
		}
		temp = temp->next;
	}
}
