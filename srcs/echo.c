/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:05:27 by aball             #+#    #+#             */
/*   Updated: 2022/10/14 19:32:36 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**echo_parse(char **echo, int *i)
{

}

int	my_echo(char **echo)
{
	size_t	i;
	char	**print;

	i = 1;
	print = echo_parse(echo, i);
	return (0);
}