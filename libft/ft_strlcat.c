/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 22:48:08 by aball             #+#    #+#             */
/*   Updated: 2021/12/22 00:54:38 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	x;
	size_t	y;
	size_t	len;

	j = 0;
	x = ft_strlen(src);
	y = ft_strlen(dst);
	i = y;
	len = dstsize - y - 1;
	if (dstsize == 0)
		return (x);
	if (y == dstsize)
		return (x + y);
	if (y > dstsize)
		return (dstsize + x);
	while (src[j] && len--)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (x + y);
}
