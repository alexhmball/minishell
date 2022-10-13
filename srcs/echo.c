/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:05:27 by aball             #+#    #+#             */
/*   Updated: 2022/10/13 13:28:23 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	my_echo(char *echo, int flag)
{
	int	i;

	i = flag;
	while (echo[i] == 'n')
		i++;
	while (echo[i] == ' ')
		i++;
	printf("%s", echo + i);
	if (flag == 4)
		printf("\n");
	return (0);
}