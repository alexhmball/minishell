# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aball <aball@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/28 20:56:59 by aball             #+#    #+#              #
#    Updated: 2022/04/03 17:02:52 by aball            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

INCLUDES = ft_printf.h ft_printf_bonus.h

SRCS = ft_putchar.c ft_putstr.c ft_putnbr.c ft_printf.c ft_putnbr_uns.c ft_hex.c \
		ft_strlen.c ft_hex_up.c ft_putaddress.c

BONUS = ft_printf_bonus.c ft_putchar_bonus.c ft_putstr_bonus.c ft_putnbr_bonus.c \
		ft_putnbr_uns_bonus.c ft_hex_bonus.c ft_strlen_bonus.c ft_hex_up_bonus.c \
		ft_putaddress_bonus.c

OBJS = ${SRCS:c=o}

BOBJS = ${BONUS:c=o}

CC = gcc

RM = rm -f

FLAGS = -Wall -Wextra -Werror

.c.o: ${SRCS}
		${CC} -g ${FLAGS} -c $< -o ${<:c=o}

$(NAME): ${OBJS}
		ar rsc ${NAME} ${OBJS}

all:	${NAME}

bonus: ${BOBJS}
		ar crs ${NAME} ${BOBJS}

clean:
		${RM} ${OBJS} ${BOBJS}

fclean: clean
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re bonus