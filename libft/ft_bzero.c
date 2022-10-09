/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 18:41:39 by aball             #+#    #+#             */
/*   Updated: 2022/06/17 19:15:57 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//function that fills memory with 0
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*dest;
	unsigned int	i;

	i = 0;
	dest = (unsigned char *)s;
	while (n--)
		dest[i++] = '\0';
}
