/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:01:28 by aball             #+#    #+#             */
/*   Updated: 2022/12/14 18:52:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	special_check(char *s, size_t *end, size_t *start)
{
	if (s[*end] && is_special(s[*end]))
	{
		*start = *end;
		while (s[*end] && is_special(s[*end]))
		{
			if (s[*end + 1] && s[*end] != s[*end + 1])
			{
				*end += 1;
				break ;
			}
			*end += 1;
		}
		return (1);
	}
	return (0);
}

static char	**cut(char const *s, char **split, int single_q, int double_q)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	while (s[end])
	{
		while (s[end] && is_spc_tb(s[end]))
			end++;
		start = end;
		while (s[end] && (single_q || double_q || !is_spc_tb(s[end]))
			&& (single_q || double_q || !is_special(s[end])))
			check_quotes(s[end++], &single_q, &double_q);
		if (s[end] && (is_spc_tb(s[end]) || is_special(s[end])))
			split = append_str(split, ft_substr(s, start, end - start));
		if (special_check((char *)s, &end, &start))
			split = append_str(split, ft_substr(s, start, end - start));
	}
	if (s[end] == 0 && !is_spc_tb(s[end - 1]))
		split = append_str(split, ft_substr(s, start, end - start));
	return (split);
}

char	**special_split(char const *s)
{
	char		**split;
	int			i;

	if (!s)
		return (0);
	if (!s || !*s)
		return (NULL);
	split = (char **)malloc(1 * sizeof(char *));
	if (!split)
		return (0);
	split[0] = 0;
	split = cut(s, split, 0, 0);
	i = 0;
	while (split[i])
	{
		if (!split[i][0])
		{
			split = remove_str(split, i);
			i = -1;
		}
		i++;
	}
	return (split);
}
