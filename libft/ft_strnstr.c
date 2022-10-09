/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:54:08 by aball             #+#    #+#             */
/*   Updated: 2022/03/28 22:12:02 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[i] == 0)
		return ((char *)&haystack[i]);
	while (haystack[i] && i < len)
	{
		i -= j;
		j = 0;
		while (needle[j] == haystack[i] && needle[j] && i < len)
		{
			i++;
			j++;
		}
		if (needle[0] == haystack[i - j] && needle[j] == 0)
			return ((char *)&haystack[i - j]);
		i++;
	}
	return (0);
}
