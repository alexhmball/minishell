/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:52:10 by aball             #+#    #+#             */
/*   Updated: 2022/01/27 16:52:11 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joint;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (0);
	joint = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!joint)
		return (0);
	while (s1[i])
	{
		joint[i] = s1[i];
		i++;
	}
	while (s2[j])
		joint[i++] = s2[j++];
	joint[i] = '\0';
	return (joint);
}
