/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:05:42 by aball             #+#    #+#             */
/*   Updated: 2022/11/09 19:15:26 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quotes(char c, int *single_q, int *double_q)
{
	if (c == '"' && !*single_q && !*double_q)
	{
		*double_q = 1;
		return (1);
	}
	else if (c == 39 && !*single_q && !*double_q)
	{
		*single_q = 1;
		return (1);
	}
	else if (c == '"' && !*single_q && *double_q)
	{
		*double_q = 0;
		return (1);
	}
	else if (c == 39 && *single_q && !*double_q)
	{
		*single_q = 0;
		return (1);
	}
	return (0);
}

char	**remove_quotes(char *line, int single_q, int double_q)
{
	int		i;
	int		x;
	char	**new_line;

	i = string_count(line);
	new_line = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	x = 0;
	while (line[i])
	{
		new_line[x] = NULL;
		while (is_spc_tb(line[i]) && line[i])
			i++;
		while (line[i] && (single_q || double_q || !is_spc_tb(line[i])))
		{
			if (!check_quotes(line[i], &single_q, &double_q) && line[i])
				new_line[x] = add_char(new_line[x], line[i]);
			i++;
		}
		x++;
	}
	new_line[x] = NULL;
	return (new_line);
}

void	insert_expand(char *new_line, char *line, char *exp, char *temp)
{
	int	i;
	int	x;
	int	save;

	i = 0;
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
}

char	*expand(char *line, int *i, int *single_q, int *double_q)
{
	char	*exp;
	char	*temp;
	char	*new_line;
	int		len;

	*i += 1;
	len = *i;
	while (ft_isalnum(line[len]) && !is_spc_tb(line[len]) && !is_q(line[len]))
		len++;
	temp = (char *)malloc(sizeof(char) * (len - *i));
	ft_strlcpy(temp, line + *i, len - *i + 1);
	exp = getenv(temp);
	if (!exp)
		exp = (char *)ft_calloc(1, sizeof(char));
	len = ft_strlen(line) - ft_strlen(temp);
	len += ft_strlen(exp) - 1;
	new_line = (char *)malloc(sizeof(char) * len);
	insert_expand(new_line, line, exp, temp);
	free (line);
	free (temp);
	*i = 0;
	*single_q = 0;
	*double_q = 0;
	return (new_line);
}

char	**quote_validator(char *line, int single_q, int double_q)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && !single_q && !is_spc_tb(line[i + 1])
			&& line[i + 1] && !is_q(line[i + 1]))
			line = expand(line, &i, &single_q, &double_q);
		if (!line)
			return (NULL);
		if (line[i] == '"' && !single_q && !double_q)
			double_q = 1;
		else if (line[i] == 39 && !single_q && !double_q)
			single_q = 1;
		else if (line[i] == '"' && !single_q && double_q)
				double_q = 0;
		else if (line[i] == 39 && single_q && !double_q)
			single_q = 0;
		i++;
	}
	if (!single_q && !double_q)
		return (remove_quotes(line, 0, 0));
	return (NULL);
}
