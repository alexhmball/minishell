# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ballzball <ballzball@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 20:53:37 by aball             #+#    #+#              #
#    Updated: 2022/12/14 05:16:37 by ballzball        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = main parsing echo quotes freedom utils pwd cd env expand unset check export \
		str_utils linked_list path init error execute linked_list_utils pipex \
		linked_list_utils2 setting_up_fds special_split exit group_args \
		here_doc flag flag_in flag_out env_list str_utils2 insert signals \
		parse_str lowering

OBJDIR = objects

OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(FILES)))

RM = rm -fr

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror -I  /usr/local/Cellar/readline/8.1/include

INCLUDE = include/minishell.h

$(OBJDIR)/%.o : srcs/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: libft $(NAME)
	@tput setaf 1
	@printf '  ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    \n'
	@printf ' ▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    \n'
	@printf ' ▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    \n'
	@printf ' ▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    \n'
	@printf ' ▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒\n'
	@printf ' ░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░\n'
	@printf ' ░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░\n'
	@printf ' ░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   \n'
	@printf '        ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░\n'
	@tput setaf 8
	@printf '	 						   Talal & Alex\n'
	@tput setaf 2
	@printf 'Executable Compiled\n'
	@tput setaf 7

$(NAME): ${OBJS}
	${CC} ${CFLAGS} $^ libft/libft.a -o $@ -L /usr/local/Cellar/readline/8.1/lib -lreadline -ltermcap

libft:
	make -C libft

clean:
	${RM} ${OBJDIR}
	make clean -C libft

fclean: clean
	${RM} $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean libft fclean re
