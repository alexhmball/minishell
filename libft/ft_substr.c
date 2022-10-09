/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 23:16:25 by aball             #+#    #+#             */
/*   Updated: 2022/08/28 19:38:00 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	slen;

	i = 0;
	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (len > slen)
		len = slen;
	if (start > slen)
		len = 0;
	if (len + start > slen)
		len = len - start;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (0);
	if (start < slen)
	{
		while (len-- && s[start])
			sub[i++] = (char)s[start++];
	}
	sub[i] = '\0';
	return (sub);
}
