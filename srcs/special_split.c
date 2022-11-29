/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:01:28 by aball             #+#    #+#             */
/*   Updated: 2022/11/29 21:21:23 by aball            ###   ########.fr       */
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
		check_quotes(s[i], &single_q, &double_q);
		if (is_spc_tb(s[i]) && i != 0 && !is_spc_tb(s[i - 1]) && s[i] && !single_q && !double_q)
			j++;
		i++;
	}
	if (s[i] == 0 && len != 0 && !is_spc_tb(s[i - 1]))
		j++;
	return (j + 1);
}

static char	**cut(char const *s, char **split, int single_q, int double_q)
{
	size_t	start;
	size_t	end;
	size_t	k;

	start = 0;
	end = 0;
	k = 0;
	while (s[end])
	{
		start = end;
		while (s[end] && is_spc_tb(s[end]))
		{
			start++;
			end++;
		}
		while (s[end] && (single_q || double_q || !is_spc_tb(s[end])))
		{
			check_quotes(s[end], &single_q, &double_q);
			end++;
		}
		if (s[end] && is_spc_tb(s[end]))
			split[k++] = ft_substr(s, start, end - start);
	}
	if (s[end] == 0 && !is_spc_tb(s[end - 1]))
		split[k++] = ft_substr(s, start, end - start);
	split[k] = 0;
	return (split);
}

char	**special_split(char const *s)
{
	char		**split;
	int			d;

	if (!s)
		return (0);
	d = word_count(s);
	printf("word count: %d\n", d);
	if (*s == 0)
		return (NULL);
	split = (char **)malloc((d + 1) * sizeof(char *));
	if (!split)
		return (0);
	return (cut(s, split, 0, 0));
}
