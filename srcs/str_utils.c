/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:56:04 by aball             #+#    #+#             */
/*   Updated: 2022/12/08 04:56:21 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**append_str(char **str, char *append)
{
	int		i;
	int		size;
	char	**new;

	if (*str)
		size = two_d_strlen(str) + 2;
	else
		size = 2;
	// write(1, "hi\n", 3);
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

char	*add_char(char *s1, char c)
{
	char	*ret;
	int		i;
	int		len;

	if (!s1)
		len = 0;
	else
		len = ft_strlen(s1);
	ret = (char *)malloc(sizeof(char) * (len + 2));
	if (!ret)
		return (NULL);
	i = 0;
	while (len > 0 && s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i++] = c;
	ret[i] = '\0';
	my_free (s1);
	return (ret);
}
