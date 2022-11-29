/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:01:28 by aball             #+#    #+#             */
/*   Updated: 2022/11/29 20:25:31 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	word_count(const char *s)
{
	int		i;
	int		j;
	int		single_q;
	int		double_q;
	size_t	len;

	i = 0;
	j = 0;
	single_q = 0;
	double_q = 0;
	len = ft_strlen(s);
	while (s[i])
	{
		check_quotes(s[i], single_q, double_q);
		if (is_spc_tb(s[i]) && i != 0 && !is_spc_tb(s[i - 1]) && s[i] && !single_q && !double_q)
			j++;
		i++;
	}
	if (s[i] == 0 && len != 0 && !is_spc_tb(s[i - 1]))
		j++;
	return (j);
}

static char	**cut(char const *s, char **split, int single_q, int double_q)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	len;

	i = 0;
	j = 0;
	k = 0;
	len = ft_strlen(s);
	while (s[j])
	{
		while (is_spc_tb(s[j]) && j <= len)
			i++;
		while (s[j] != c && j < len)
			j++;
		if (s[j] == c && j < len)
		{
			split[k++] = ft_substr(s, i, j - i);
			i = j;
		}
		j++;
	}
	if (s[j] == 0 && s[j - 1] != c)
		split[k] = ft_substr(s, i, j - i);
	return (split);
}

char	**special_split(char const *s)
{
	char		**split;
	int			d;

	if (!s)
		return (0);
	d = word_count(s);
	if (*s == 0)
		return (NULL);
	split = (char **)malloc((d + 1) * sizeof(char *));
	if (!split)
		return (0);
	split[d] = 0;
	return (cut(s, split, 0, 0));
}
