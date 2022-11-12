/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:53:03 by aball             #+#    #+#             */
/*   Updated: 2022/11/12 23:48:42 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	my_unset(t_cmd *args)
{
	t_list	*current;
	t_list	*temp;
	size_t	len;
	int		i;

	current = *args->env;
	temp = current;
	i = 0;
	if (two_d_strlen(args->cmd) > 1)
	{
		while (current)
		{
			len = find_equal(current->content);
			if (len >= ft_strlen(args->cmd[1])
				&& !ft_strncmp(current->content, args->cmd[1], len))
			{
				temp->next = current->next;
				ft_lstdelone(current, free);
				current = temp;
				if (i == 0)
					args->env = &temp->next;
			}
			temp = current;
			current = current->next;
			i++;
		}
	}
}
