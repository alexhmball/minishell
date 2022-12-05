/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:37:06 by aball             #+#    #+#             */
/*   Updated: 2022/12/03 00:56:56 by talsaiaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_working_dir(void)
{
	char	*buf;

	buf = (char *)malloc(sizeof(char) * PATH_MAX);
	getcwd(buf, PATH_MAX);
	return (buf);
}

void	print_working_dir(void)
{
	char	*buf;

	buf = (char *)malloc(sizeof(char) * PATH_MAX);
	getcwd(buf, PATH_MAX);
	printf("%s\n", buf);
	my_free(buf);
}
