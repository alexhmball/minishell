/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 21:34:04 by aball             #+#    #+#             */
/*   Updated: 2022/12/09 22:43:14 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clear_env(t_env **head)
{
	t_env	*temp;

	if (!head)
		return ;
	while (*head)
	{
		temp = (*head)->next;
		if ((*head)->key)
			my_free((*head)->key);
		if ((*head)->value)
			my_free((*head)->value);
		my_free(*head);
		*head = temp;
	}
	// my_free(head);
}

void	env_delone(t_env *node)
{
	if (!node)
		return ;
	if (node->key)
		my_free(node->key);
	if (node->value)
		my_free(node->value);
	if (node)
		my_free(node);
}

t_env	*env_addback(t_env **head, t_env *node)
{
	t_env	*temp;

	if (!head || !node)
		return (NULL);
	if (!*head)
	{
		*head = node;
		return (node);
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
	return (node);
}

t_env	*env_newlst(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

char	*get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (i == (int)ft_strlen(str))
		return (NULL);

	i++;
	j = i;
	while (str[j])
		j++;
	value = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!value)
		return (NULL);
	j = 0;
	while (str[i])
	{
		value[j] = str[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}
