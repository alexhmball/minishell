/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 02:11:03 by talsaiaa          #+#    #+#             */
/*   Updated: 2022/12/07 21:18:16 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	gnl_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*joint;

	i = 0;
	j = 0;
	if (s1 == 0)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (s2 == 0)
		return (0);
	joint = (char *)malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (joint == 0)
		return (0);
	while (s1[i])
		joint[j++] = s1[i++];
	i = 0;
	while (s2[i])
		joint[j++] = s2[i++];
	joint[j] = '\0';
	free(s1);
	return (joint);
}

char	*gnl_strchr(const char *s, int c)
{
	unsigned int	i;
	unsigned char	*dest;

	i = 0;
	if (!s)
		return (0);
	dest = (unsigned char *)s;
	while (dest[i])
	{
		if (dest[i] == (unsigned char )c)
			return (&((char *)dest)[i]);
		i++;
	}
	if (c == '\0')
		return (&((char *)dest)[i]);
	return (0);
}

char	*gnl_strdup(char *s1)
{
	int		i;
	char	*dest;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i])
		i++;
	dest = (char *)malloc(i + 1);
	i = 0;
	if (dest == 0)
		return (0);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
