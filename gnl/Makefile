# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: talsaiaa <talsaiaa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/07 21:02:10 by talsaiaa          #+#    #+#              #
#    Updated: 2022/12/07 21:13:48 by talsaiaa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a

SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c 

INCLUDES = get_next_line_bonus.h

OBJS = ${SRCS:c=o}

CC		= gcc
RM		= rm -f

FLAGS = -Wall -Wextra -Werror

all: ${NAME}

%.o: %.c ${SRCS}
		${CC} ${FLAGS} -c $< -o ${<:c=o}

$(NAME): ${OBJS}
		ar crs ${NAME} ${OBJS}

clean:
		${RM} ${OBJS} 

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY: fclean all re clean