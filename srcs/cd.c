/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:36:24 by aball             #+#    #+#             */
/*   Updated: 2022/11/12 22:46:00 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	change_dir(char **cmd, t_cmd *args)
{
	char	*path;

	if (two_d_strlen(cmd) > 1)
		path = cmd[1];
	else
		path = my_getenv("HOME", args);
	if (chdir(path) != 0)
	{
		if (errno == ENOTDIR)
			printf("cd: %s: Not a directory\n", cmd[1]);
		if (errno == ENOENT)
			printf("cd: %s: No such file or directory\n", cmd[1]);
		if (errno == EACCES)
			printf("cd: %s: Permission denied\n", cmd[1]);
	}
}
