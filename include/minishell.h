/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 20:53:44 by aball             #+#    #+#             */
/*   Updated: 2022/11/12 22:52:00 by aball            ###   ########.fr       */
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

typedef struct	s_cmd
{
	char			**cmd;
	char			*path;
	char			*s;
	int				err;
	int				*expand;
	int				need_exp;
	int				pid;
	int				fd;
	DIR				*folder;
	t_list			**env;
	struct dirent	*dir;
}			t_cmd;

int		parsing(t_cmd *args);
int		count_dollar(char *str);
int		is_spc_tb(char c);
int		is_q(char c);
char	**quote_validator(t_cmd *args, int single_q, int double_q);
int		check_quotes(char c, int *single_q, int *double_q);
char	**remove_quotes(t_cmd *args, int single_q, int double_q);
void	freedom(char **free_me);
void	total_freedom(t_cmd *args);
char	*expand(char *line, int i, t_cmd *args, int x);
char	*insert_expand(char *line, char *exp, char *temp);
int		check_newline(char **echo, int *i, int len);
char	*add_char(char *s1, char c);
int		string_count(char *line);
int		two_d_strlen(char **str);
t_list	**create_env(char **exp);
char	*find_env(char *temp, t_cmd *args);
void	check_expand(t_cmd *args);
int		find_equal(char *str);
int		check_dir(t_cmd *args);
char	*my_getenv(char *str_env, t_cmd *args);

int		my_echo(char **echo);
void	print_working_dir(void);
void	change_dir(char **cmd, t_cmd *args);
void	my_export(t_cmd *args);
void	my_env(t_cmd *args);
void	my_unset(t_cmd *args);

#endif