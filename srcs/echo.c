/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:05:27 by aball             #+#    #+#             */
/*   Updated: 2022/12/07 18:14:41 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	two_d_strlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_newline(char **echo, int *start, int len)
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
			if (i >= len)
				break ;
		}
		if (echo[i][j] != 'n')
			break ;
	}
	return (new_line);
}

int	my_echo(char **echo, t_cmd *args)
{
	int	i;
	int	counter;
	int	new_line;

	i = 1;
	counter = two_d_strlen(echo);
	new_line = check_newline(echo, &i, counter);
	if (i >= counter)
	{
		if (new_line)
			printf("\n");
		return (0);
	}
	counter = 0;
	while (echo[i])
	{
		if (counter > 0)
			printf(" ");
		printf("%s", echo[i]);
		i++;
		counter++;
	}
	if (new_line)
		printf("\n");
	*args->err = 0;
	return (0);
}
