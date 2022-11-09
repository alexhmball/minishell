/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 20:53:44 by aball             #+#    #+#             */
/*   Updated: 2022/11/09 18:47:25 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <limits.h>
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

int		parsing(void);
// char	**special_split(char *cmd);
int		is_spc_tb(char c);
int		is_q(char c);
char	**quote_validator(char *line, int single_q, int double_q);
int		check_quotes(char c, int *single_q, int *double_q);
char	**remove_quotes(char *line, int single_q, int double_q);
void	freedom(char **free_me);
char	*expand(char *line, int *i, int *single_q, int *double_q);
void	insert_expand(char *new_line, char *line, char *exp, char *temp);
int		check_newline(char **echo, int	*i);
char	*add_char(char *s1, char c);
int		string_count(char *line);

int		my_echo(char **echo);
void	print_working_dir(void);
void	change_dir(char **cmd);

#endif