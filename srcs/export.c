/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:53:39 by aball             #+#    #+#             */
/*   Updated: 2022/11/22 18:43:48 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	compare_env(t_cmd *args)
{
	t_list	*current;
	int		len;
	int		len_env;

	current = *args->env;
	len = find_equal(args->cmd[1]);
	if (two_d_strlen(args->cmd) > 1 && len != -1)
	{
		while (current)
		{
			len_env = find_equal(current->content);
			if (len_env == len)
				if (!ft_strncmp(current->content, args->cmd[1], len))
				{
					my_free(current->content);
					current->content = ft_strdup(args->cmd[1]);
					return (1);
				}
			current = current->next;
		}
	}
	return (0);
}

void	my_export(t_cmd *args)
{
	t_list	*temp;

	temp = *args->env;
	if (two_d_strlen(args->cmd) > 1 && !compare_env(args))
	{
		while (temp)
		{
			if (ft_strlen(temp->content) == ft_strlen(args->cmd[1])
				&& !ft_strncmp(temp->content, args->cmd[1],
					ft_strlen(args->cmd[1])))
				return ;
			temp = temp->next;
		}
		if (find_equal(args->cmd[1]) != -1)
			ft_lstadd_back(args->env, ft_lstnew(ft_strdup(args->cmd[1])));
	}
	else if (two_d_strlen(args->cmd) <= 1)
	{
		while (temp)
		{
			printf("declare -x %s\n", (char *)temp->content);
			temp = temp->next;
		}
	}
}
