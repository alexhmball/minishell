/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:37:28 by aball             #+#    #+#             */
/*   Updated: 2022/11/12 23:07:12 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	**create_env(char **exp)
{
	t_list	**head;
	t_list	*temp;
	int		i;

	i = 0;
	head = (t_list **)malloc(sizeof(t_list *));
	temp = ft_lstnew(ft_strdup(exp[i]));
	*head = temp;
	i++;
	while (exp[i])
	{
		ft_lstadd_back(head, ft_lstnew(ft_strdup(exp[i])));
		i++;
	}
	return (head);
}

char	*find_env(char *temp, t_cmd *args)
{
	t_list	*current;
	int		i;
	char	*ret;

	current = *args->env;
	i = 0;
	while (current)
	{
		if (!ft_strncmp(temp, current->content, ft_strlen(temp)))
		{
			while (((char *)current->content)[i] != '=')
				i++;
			i++;
			ret = ft_strdup(((char *)current->content) + i);
			return (ret);
		}
		current = current->next;
	}
	return (NULL);
}

void	my_env(t_cmd *args)
{
	t_list	*temp;

	temp = *args->env;
	while (temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
}

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}
