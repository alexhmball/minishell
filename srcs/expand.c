/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:58:39 by aball             #+#    #+#             */
/*   Updated: 2022/11/15 22:09:13 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*insert_expand(char *line, char *exp, char *temp)
{
	int	i;
	int	x;
	int	save;
	int	len;
	char *new_line;

	i = 0;
	len = ft_strlen(line) - ft_strlen(temp);
	len += ft_strlen(exp) - 1;
	new_line = (char *)malloc(sizeof(char) * len);
	while (line[i] != '$' && line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	save = i;
	x = 0;
	while (exp[x])
		new_line[i++] = exp[x++];
	save += ft_strlen(temp) + 1;
	while (line[save])
		new_line[i++] = line[save++];
	new_line[i] = 0;
	return (new_line);
}

char	*expand(char *line, int i, t_cmd *args, int x)
{
	char	*exp;
	char	*temp;
	char	*new_line;
	int		len;

	i++;
	len = i;
	while (!is_spc_tb(line[len]) && !is_q(line[len]) && line[len])
		len++;
	temp = (char *)malloc(sizeof(char) * (len - i));
	ft_strlcpy(temp, line + i, len - i + 1);
	if (args->expand[x])
		exp = my_getenv(temp, args);
	else
		exp = ft_strjoin("$", temp);
	if (!exp)
		exp = (char *)ft_calloc(1, sizeof(char));
	new_line = insert_expand(line, exp, temp);
	free (line);
	free (temp);
	free (exp);
	return (new_line);
}

int	locate_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

void	check_expand(t_cmd *args)
{
	int		i;
	int		x;
	int		pos;
	char	*temp;

	i = 0;
	x = 0;
	while (args->cmd[i])
	{
		pos = locate_dollar(args->cmd[i]);
		if (pos != -1)
		{
			temp = expand(args->cmd[i], pos, args, x);
			args->cmd[i] = ft_strdup(temp);
			x++;
		}
		i++;
	}
}
