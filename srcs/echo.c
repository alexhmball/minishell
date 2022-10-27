/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:05:27 by aball             #+#    #+#             */
/*   Updated: 2022/10/26 21:53:18 by ballzball        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	check_newline(char **echo)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (echo[i])
// 	{

// 	}
// }

int	my_echo(char **echo)
{
	int	i;
	// int	new_line;

	i = 1;
	// new_line = check_newline(echo);
	while (echo[i])
		printf("%s ", echo[i++]);
	// if (new_line)
		printf("\n");
	return (0);
}