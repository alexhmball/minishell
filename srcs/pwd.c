/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:37:06 by aball             #+#    #+#             */
/*   Updated: 2022/11/09 18:40:27 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_working_dir(void)
{
	char	*buf;

	buf = (char *)malloc(sizeof(char) * PATH_MAX);
	getcwd(buf, PATH_MAX);
	printf("%s\n", buf);
	free(buf);
}
