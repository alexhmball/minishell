# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aball <aball@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 20:53:37 by aball             #+#    #+#              #
#    Updated: 2022/10/09 23:45:13 by aball            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = main.c

SRCS = $(addprefix srcs/, ${FILES})

OBJS = ${SRCS:c=o}

RM = rm -fr

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

all: libft $(NAME)

$(NAME): ${OBJS}
	${CC} ${CFLAGS} -lreadline libft/libft.a $^ -o $@

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