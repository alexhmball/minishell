/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:56:04 by aball             #+#    #+#             */
/*   Updated: 2022/11/22 21:44:40 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**append_str(char **str, char *append)
{
	int		i;
	int		size;
	char	**new;

	size = two_d_strlen(str) + 2;
	new = (char **)malloc(sizeof(char *) * size);
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = ft_strdup(str[i]);
		i++;
	}
	new[i++] = ft_strdup(append);
	new[i] = NULL;
	freedom(str);
	return (new);
}

char	**remove_str(char **str, int index)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	new = (char **)malloc(sizeof(char *) * two_d_strlen(str));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (i != index)
		{
			new[j] = ft_strdup(str[i]);
			j++;
		}
		i++;
	}
	new[j] = NULL;
	freedom(str);
	return (new);
}
