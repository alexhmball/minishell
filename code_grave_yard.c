// char	*insert_expand(char *line, char *exp, char *temp)
// {
// 	int		i;
// 	int		x;
// 	int		save;
// 	int		len;
// 	char	*new_line;

// 	i = 0;
// 	len = ft_strlen(line) - ft_strlen(temp);
// 	len += ft_strlen(exp) - 1;
// 	new_line = (char *)malloc(sizeof(char) * len + 1);
// 	while (line[i] != '$' && line[i])
// 	{
// 		new_line[i] = line[i];
// 		i++;
// 	}
// 	save = i;
// 	x = 0;
// 	while (exp[x])
// 		new_line[i++] = exp[x++];
// 	save += ft_strlen(temp) + 1;
// 	while (line[save])
// 		new_line[i++] = line[save++];
// 	new_line[i] = 0;
// 	return (new_line);
// }

// char	*expand(char *line, int i, t_cmd *args)
// {
// 	char	*exp;
// 	char	*temp;
// 	char	*new_line;
// 	int		len;

// 	i++;
// 	len = i;
// 	if (line[locate_dollar(line) + 1] == '?')
// 	{
// 		new_line = insert_error(line, args);
// 		return (new_line);
// 	}
// 	while (!is_spc_tb(line[len]) && !is_q(line[len]) && line[len])
// 		len++;
// 	temp = (char *)malloc(sizeof(char) * (len - i) + 1);
// 	ft_strlcpy(temp, line + i, len - i + 1);
// 	temp[len - i] = 0;
// 	exp = my_getenv(temp, args);
// 	if (!exp)
// 		exp = (char *)ft_calloc(1, sizeof(char));
// 	new_line = insert_expand(line, exp, temp);
// 	my_free (line);
// 	my_free (temp);
// 	my_free (exp);
// 	return (new_line);
// }



// void	check_expand(t_pipe *node, t_cmd *args)
// {
// 	int		pos;
// 	char	*ret;
//
// 	pos = locate_dollar(node->cmd[0]);
// 	if (pos != -1 && !node->single_q)
// 	{
// 		ret = expand(node->cmd[0], pos, args);
// 		node->cmd[0] = ret;
// 	}
// }
