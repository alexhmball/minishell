/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:37:28 by aball             #+#    #+#             */
/*   Updated: 2022/11/12 00:34:35 by ballzball        ###   ########.fr       */
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
	temp = ft_lstnew(exp[i]);
	*head = temp;
	i++;
	while(exp[i])
	{
		ft_lstadd_back(head, ft_lstnew(exp[i]));
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

void	my_export(t_cmd *args)
{
	t_list	*temp;

	if (two_d_strlen(args->cmd) > 1)
	{
		temp = *args->env;
		while (temp)
		{
			if (ft_strlen(temp->content) == ft_strlen(args->cmd[1])
				&& !ft_strncmp(temp->content, args->cmd[1], ft_strlen(args->cmd[1])))
				return ;
			temp = temp->next;
		}
		if (find_equal(args->cmd[1]) != -1)
			ft_lstadd_back(args->env, ft_lstnew(ft_strdup(args->cmd[1])));
	}
	else
	{
		temp = *args->env;
		while (temp)
		{
			printf("declare -x %s\n", (char *)temp->content);
			temp = temp->next;
		}
	}
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

void	my_unset(t_cmd *args)
{
	t_list	*current;
	t_list	*temp;
	size_t	len;

	current = *args->env;
	if (two_d_strlen(args->cmd) > 1)
	{
		while (current)
		{
			len = find_equal(current->content);
			if (len >= ft_strlen(args->cmd[1]) && !ft_strncmp(current->content, args->cmd[1], len))
			{
				temp->next = current->next;
				current->next = NULL;
				ft_lstdelone(current, free);
				current = temp;
			}
			temp = current;
			current = current->next;
		}
	}
}