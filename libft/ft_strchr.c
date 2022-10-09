/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 01:24:42 by aball             #+#    #+#             */
/*   Updated: 2022/01/27 16:51:02 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	while (ptr[i])
	{
		if ((unsigned char)ptr[i] == (unsigned char)c)
			return (&ptr[i]);
		i++;
	}
	if (c == '\0')
		return (&ptr[i]);
	return (0);
}
