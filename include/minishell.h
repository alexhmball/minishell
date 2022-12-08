/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 20:53:44 by aball             #+#    #+#             */
/*   Updated: 2022/12/08 23:11:47 by aball            ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_pipe
{
	int				is_pipe;
	int				in;
	int				out;
	int				here_doc;
	int				append;
	int				single_q;
	int				double_q;
	char			*path;
	char			**cmd;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_cmd
{
	char				**cmd;
	char				*path;
	char				*s;
	int					*err;
	int					need_exp;
	int					pid;
	int					fd;
	int					pipe_n;
	int					redirect;
	char				**env_for_excecute;
	char				*err_msg;
	DIR					*folder;
	t_list				**env;
	t_pipe				**pipe;
	struct dirent		*dir;
}	t_cmd;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~PARSING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int		parsing(t_cmd *args);
int		count_dollar(char *str);
int		is_spc_tb(char c);
int		is_q(char c);
char	**quote_validator(t_cmd *args, int single_q, int double_q);
int		check_quotes(char c, int *single_q, int *double_q);
void	remove_quotes(t_pipe **h, int single_q, int double_q, t_cmd *args);
char	*expand(char *line, int i, t_cmd *args);
char	*insert_expand(char *line, char *exp, char *temp);
char	*add_char(char *s1, char c);
int		string_count(char *line);
int		two_d_strlen(char **str);
t_list	**create_env(char **exp);
char	*find_env(char *temp, t_cmd *args);
void	check_expand(t_pipe *node, t_cmd *args);
int		find_equal(char *str);
int		check_dir(t_cmd *args);
char	*my_getenv(char *str_env, t_cmd *args);
char	*get_working_dir(void);
int		validate_dir(t_cmd *args, char *search, char *cmd);
int		validate_path(char	*cmd, t_cmd *args);
char	**append_str(char **str, char *append);
int		check_path(t_cmd *args);
int		check_single_path(char *cmd);
int		locate_dollar(char *str);
void	init_struct(t_cmd *args);
void	set_error(t_cmd *args, int code);
int		search_all_paths(t_cmd *args, char **search);
int		search_current_dir(t_cmd *args, char *current);
char	**remove_str(char **str, int index);
char	**special_split(char const *s);
void	confirm_path(t_cmd *args);
char	*insert_error(char *line, t_cmd *args);
void	find_errors(t_cmd *args, t_pipe **head);
void	expand_dollar(t_pipe *node, t_cmd *args);
void	find_expand(t_pipe *current, int single_q, int double_q, t_cmd *args);
void	flag_quotes(t_pipe *node, int *single_q, int *double_q);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~EXECUTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int		is_us(t_pipe *cmd);
int		check_exec(t_cmd *args);
void	excecute_us(t_cmd *args, t_pipe *cmd);
void	execute_them(t_cmd *args, t_pipe *cmd);
void	pipex(t_cmd *args);
void	setting_up_ins(t_pipe *temp, int *prev_pipe, t_cmd *args, t_pipe *cmd, int ms_hd, int (*fd));
void	setting_up_outs(t_pipe *temp, t_cmd *args, int (*fd), int *prev_out);
void	ms_heredoc(t_pipe *temp, t_cmd *args, t_pipe *cmd, int (*fd));

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~MEMORY_MANAGEMENT~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void	my_free(void *content);
int		freedom(char **free_me);
void	total_freedom(t_cmd *args);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~LINKED_LIST~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

t_pipe	*lstnew_pipe(char *content, char *path);
void	lstadd_back_pipe(t_pipe **lst, t_pipe *new);
t_pipe	*lstlast_pipe(t_pipe *lst);
void	lstclear_pipe(t_pipe **lst, void (*del)(void *));
void	lstdelone_pipe(t_pipe *lst, void (*del)(void *));
void	swap_node(t_pipe *node1, t_pipe *node2, t_pipe **head, int c);
void	organize_cmds(t_cmd *args);
int		flag_list(t_cmd *args);
void	parse_args_back(t_cmd *args, int i);
void	create_pipe_list(t_cmd *args);
t_pipe	*my_lst_last(t_pipe *temp);
size_t	my_lst_size(t_pipe *temp);
void	find_cmd_args(t_cmd *args);
t_pipe	*ret_pipe_location(t_pipe **head, int node);
t_pipe	*remove_node(t_pipe **head, t_pipe *node, t_pipe *prev_node, int c);
t_pipe	*pre_pipe(t_pipe **head, int count);
void	print_pipe(t_pipe **head);
void	flag_pipe(t_cmd *args);
void	flag_in(t_cmd *args);
void	flag_here_doc(t_cmd *args);
void	flag_out(t_cmd *args);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~BUILT_IN~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int		my_echo(char **echo, t_cmd *args);
void	print_working_dir(void);
void	change_dir(char **cmd, t_cmd *args);
void	my_export(t_cmd *args, t_pipe *node);
void	my_env(t_cmd *args);
void	my_unset(t_cmd *args);
void	child_rangler(int signo, siginfo_t *info, void *context);
void	exit_shell(t_cmd *args, t_pipe *node);
void	us_not_printing(t_cmd *args);

#endif
