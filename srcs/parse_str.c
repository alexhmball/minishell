/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:19:59 by ballzball         #+#    #+#             */
/*   Updated: 2022/12/14 20:52:08 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_special(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	is_special_char(char c, char *str, int i)
{
	if (c == '|' || c == '>' || c == '<')
	{
		if (str[i + 1] && str[i + 1] == c)
			return (0);
		return (1);
	}
	return (0);
}
