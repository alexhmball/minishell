/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:37:06 by aball             #+#    #+#             */
/*   Updated: 2022/12/02 22:45:03 by talsaiaa         ###   ########.fr       */
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

void	print_working_dir(int fd)
{
	char	*buf;

	buf = (char *)malloc(sizeof(char) * PATH_MAX);
	getcwd(buf, PATH_MAX);
	ft_putstr_fd(buf, fd);
	ft_putchar_fd('\n', fd);
	my_free(buf);
}
