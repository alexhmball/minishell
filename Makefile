# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aball <aball@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 20:53:37 by aball             #+#    #+#              #
#    Updated: 2022/11/11 00:00:18 by aball            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = main parsing echo quotes freedom utils pwd cd

OBJDIR = objects

OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(FILES)))

RM = rm -fr

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror -I /usr/local/Cellar/readline/8.1/include

INCLUDE = include/minishell.h

$(OBJDIR)/%.o : srcs/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: libft $(NAME)
	@tput setaf 2
	@printf 'Executable Compiled\n'
	@tput setaf 7

$(NAME): ${OBJS}
	${CC} -fsanitize=address ${CFLAGS} $^ libft/libft.a -o $@ -L /usr/local/Cellar/readline/8.1/lib -lreadline

libft:
	make -C libft

clean:
	${RM} ${OBJDIR}
	make clean -C libft

fclean: clean
	${RM} $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean libft fclean