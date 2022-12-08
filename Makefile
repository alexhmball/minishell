# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 20:53:37 by aball             #+#    #+#              #
#    Updated: 2022/12/07 21:16:04 by talsaiaa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = main parsing echo quotes freedom utils pwd cd env expand unset check export \
		str_utils linked_list path init error execute linked_list_utils pipex \
		linked_list_utils2 setting_up_fds special_split desperation exit

OBJDIR = objects

OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(FILES)))

RM = rm -fr

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror -I  /usr/local/Cellar/readline/8.1/include

INCLUDE = include/minishell.h

$(OBJDIR)/%.o : srcs/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: libft gnl $(NAME)
	@cat talal.ansi.txt
	@tput setaf 2
	@printf 'Executable Compiled\n'
	@tput setaf 7

$(NAME): ${OBJS}
	${CC} ${CFLAGS} $^ libft/libft.a gnl/gnl.a -o $@ -L /usr/local/Cellar/readline/8.1/lib -lreadline -ltermcap

libft:
	make -C libft
gnl:
	make -C gnl

clean:
	${RM} ${OBJDIR}
	make clean -C libft
	make clean -C gnl

fclean: clean
	${RM} $(NAME)
	make fclean -C libft
	make fclean -C gnl

re: fclean all

.PHONY: all clean libft gnl fclean