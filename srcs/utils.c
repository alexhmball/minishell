/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:35:15 by aball             #+#    #+#             */
/*   Updated: 2022/11/07 10:11:50 by aball            ###   ########.fr       */
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

char	*join_str(char *s1, char *s2, int size, int start)
{
	int		len;
	int		i;
	char	*ret;

	i = 0;
	len = ft_strlen(s1) + size + 1;
	ret = (char *)malloc(sizeof(char) * len);
	printf("%d\n", len);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (i < len && s2[start])
	{
		ret[i] = s2[start];
		i++;
		start++;
	}
	ret[i] = 0;
	return (ret);
}