/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:22:36 by aball             #+#    #+#             */
/*   Updated: 2022/10/09 23:59:49 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("\x1b[30m\x1b[46mminishell$\x1b[m ");
		if (!ft_strncmp(line, "exit", 4) && ft_strlen(line) == 4)
			exit (0);
		printf("%s\n", line);
	}
	return (0);
}