/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 03:03:10 by aball             #+#    #+#             */
/*   Updated: 2022/12/12 03:03:18 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*insert_pid(char *line, t_cmd *args)
{
	char	*err_num;
	char	*new_line;
	int		len;
	int		i;
	int		j;

	err_num = ft_itoa(args->pid);
	len = ft_strlen(err_num) + ft_strlen(line);
	new_line = (char *)malloc(sizeof(char) * (len));
	i = 0;
	j = 0;
	while (line[i] && line[i] != '$')
	{
		new_line[i] = line[i];
		i++;
	}
	len = i + 2;
	while (err_num[j])
		new_line[i++] = err_num[j++];
	while (line[len])
		new_line[i++] = line[len++];
	my_free(line);
	my_free(err_num);
	new_line[i] = 0;
	return (new_line);
}

char	*insert_error(char *line, t_cmd *args)
{
	char	*err_num;
	char	*new_line;
	int		len;
	int		i;
	int		j;

	err_num = ft_itoa(*args->err);
	len = ft_strlen(err_num) + ft_strlen(line);
	new_line = (char *)malloc(sizeof(char) * (len));
	i = 0;
	j = 0;
	while (line[i] && line[i] != '$')
	{
		new_line[i] = line[i];
		i++;
	}
	len = i + 2;
	while (err_num[j])
		new_line[i++] = err_num[j++];
	while (line[len])
		new_line[i++] = line[len++];
	my_free(line);
	my_free(err_num);
	new_line[i] = 0;
	return (new_line);
}
