# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aball <aball@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 20:53:37 by aball             #+#    #+#              #
#    Updated: 2022/10/13 20:18:39 by aball            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = main.c parsing.c echo.c

SRCS = $(addprefix srcs/, ${FILES})

OBJS = ${SRCS:c=o}

RM = rm -fr

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror -I /usr/local/Cellar/readline/8.1/include

INCLUDE = include/minishell.h

all: libft $(NAME)

$(NAME): ${OBJS}
	${CC} ${CFLAGS} $^ libft/libft.a -o $@ -L /usr/local/Cellar/readline/8.1/lib -lreadline

.o: .c
	${CC} ${CFLAGS} -c $< -o ${<:c=o}

libft:
	make -C libft

clean:
	${RM} ${OBJS}
	make clean -C libft

fclean: clean
	${RM} $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean libft fclean