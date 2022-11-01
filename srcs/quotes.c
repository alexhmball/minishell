/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:05:42 by aball             #+#    #+#             */
/*   Updated: 2022/11/01 19:58:47 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	skip_q(char c, int *single_q, int *double_q)
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
	else if (*single_q || *double_q)
		return (1);
	return (0);
}

static int		word_count(char *line, int single_q, int double_q)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (line[i])
	{
		while (skip_q(line[i], &single_q, &double_q))
			i++;
		if (is_spc_tb(line[i]))
			i++;
		else
		{
			counter++;
			i++;
		}
	}
	return (counter);
}

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

int	check_line(char *line, int start, int end)
{
	while (start < end && line[start])
	{
		if (!is_spc_tb(line[start]))
			return (1);
		start++;
	}
	return (0);
}

char	**remove_quotes(char *line, int single_q, int double_q)
{
	int		i;
	int		x;
	int		start;
	int		end;
	char	**new_line;

	i = word_count(line, single_q, double_q);
	new_line = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	start = 0;
	end = 0;
	x = 0;
	while (line[i])
	{
		while (is_spc_tb(line[i]) && line[i])
		{
			i++;
			start++;
			end++;
		}
		if (is_q(line[i]))
		{
			while (check_quotes(line[i], &single_q, &double_q) && line[i])
				i++;
			end = i;
		}
		else
		{
			while (!is_spc_tb(line[i]) && !is_q(line[i]) && line[i])
			{
				i++;
				end++;
			}
		}
		if (check_line(line, start, end))
			new_line[x++] = ft_substr(line, start, end - start);
		if (!line[i])
			break;
		start = end;
		i = end;
	}
	new_line[x] = 0;
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
	{
		new_line[i++] = exp[x++];
	}
	save += ft_strlen(temp) + 1;
	while (line[save])
	{
		new_line[i++] = line[save++];
	}
	new_line[i] = 0;
}

char	*expand(char *line, int *i)
{
	char	*exp;
	char	*temp;
	char	*new_line;
	int		len;

	*i += 1;
	len = *i;
	while (ft_isalnum(line[len]) && !is_spc_tb(line[len]))
		len++;
	temp = (char *)malloc(sizeof(char) * (len - *i));
	ft_strlcpy(temp, line + *i, len - *i + 1);
	exp = getenv(temp);
	if (!exp)
	{
		exp = (char *)malloc(sizeof(char) * 1);
		exp[0] = 0;
	}
	len = ft_strlen(line) - ft_strlen(temp);
	len += ft_strlen(exp) - 1;
	new_line = (char *)malloc(sizeof(char) * len);
	insert_expand(new_line, line, exp, temp);
	free (line);
	free (temp);
	return (new_line);
	}

char	**quote_validator(char *line, int single_q, int double_q)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && !single_q)
			line = expand(line, &i);
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