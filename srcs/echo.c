/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:05:27 by aball             #+#    #+#             */
/*   Updated: 2022/11/03 19:24:19 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_newline(char **echo, int *start)
{
	int	i;
	int	j;
	int	new_line;

	i = *start;
	j = 0;
	new_line = 1;
	while (echo[i])
	{
		if (echo[i][0] != '-')
			break ;
		j++;
		if (!echo[i][j])
		{
			*start += 1;
			new_line = 0;
			i++;
			j = 1;
		}
		if (echo[i][j] != 'n')
			break ;
	}
	return (new_line);
}

int	my_echo(char **echo)
{
	int	i;
	int	counter;
	int	new_line;

	i = 1;
	counter = 0;
	new_line = check_newline(echo, &i);
	while (echo[i])
	{
		if (counter > 0)
			printf(" ");
		printf("%s", echo[i++]);
		counter++;
	}
	if (new_line)
		printf("\n");
	return (0);
}