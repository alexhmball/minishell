/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:57:22 by aball             #+#    #+#             */
/*   Updated: 2022/01/27 21:10:09 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_start(char const *s1, char const *set)
{
	int	j;
	int	x;
	int	start;

	j = 0;
	x = 0;
	start = 0;
	while (s1[j++])
	{
		x = 0;
		while (set[x])
			if (set[x++] == s1[start])
				start++;
	}
	return (start);
}

static int	check_end(char const *s1, char const *set, int start, int end)
{
	int	j;
	int	x;

	j = end + 1;
	while (j-- > start)
	{
		x = 0;
		while (set[x])
			if (set[x++] == s1[end])
				end--;
	}
	end++;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		j;
	int		end;
	char	*trim;
	int		x;

	x = 0;
	if (!s1)
		return (0);
	j = ft_strlen(s1);
	start = check_start(s1, set);
	end = check_end(s1, set, start, j - 1);
	trim = (char *)malloc(end - start + 1);
	if (!trim)
		return (0);
	while (start < end)
		trim[x++] = s1[start++];
	trim[x] = '\0';
	return (trim);
}
