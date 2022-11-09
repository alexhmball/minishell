/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:35:15 by aball             #+#    #+#             */
/*   Updated: 2022/11/09 18:47:12 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_spc_tb(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	is_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	is_q(char c)
{
	if (c == '"' || c == 39)
		return (1);
	return (0);
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
	ret[i] = 0;
	free (s1);
	return (ret);
}

int	string_count(char *line)
{
	int		i;
	int		counter;

	i = 0;
	counter = 1;
	while (line[i])
	{
		while (is_spc_tb(line[i]) && line[i])
			i++;
		while (!is_spc_tb(line[i]) && line[i])
			i++;
		counter++;
		if (!line[i])
			break ;
		i++;
	}
	return (counter);
}
