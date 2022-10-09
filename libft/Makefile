# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aball <aball@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 14:07:38 by aball             #+#    #+#              #
#    Updated: 2022/06/24 14:40:54 by aball            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isdigit.c ft_memset.c ft_strjoin.c ft_isprint.c ft_substr.c ft_atoi.c \
	ft_tolower.c ft_strlen.c ft_toupper.c ft_calloc.c ft_memchr.c ft_isalnum.c \
	ft_memcmp.c ft_strncmp.c ft_isalpha.c ft_memcpy.c ft_strchr.c ft_strnstr.c \
	ft_isascii.c ft_memmove.c ft_strdup.c ft_strrchr.c ft_strtrim.c ft_bzero.c \
	ft_strlcpy.c ft_strlcat.c ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c \
	ft_putnbr_fd.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_split.c

SRCS += printf/ft_putchar.c printf/ft_putstr.c printf/ft_putnbr.c printf/ft_printf.c \
		printf/ft_putnbr_uns.c printf/ft_hex.c printf/ft_strlen.c printf/ft_hex_up.c \
		printf/ft_putaddress.c str_sep.c

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	ft_lstdelone.c ft_lstiter.c ft_lstclear.c ft_lstmap.c

# BONUS += ft_lstadd_back_db.c ft_lstlast_db.c ft_lstadd_front_db.c ft_lstnew_db.c \
# 		ft_lstsize_db.c ft_lstdelone_db.c ft_lstclear_db.c ft_lstiter_db.c

INCLUDES = libft.h

OBJS = ${SRCS:c=o}

OBJSBONUS = ${BONUS:c=o}

CC		= gcc
RM		= rm -f

FLAGS = -Wall -Wextra -Werror

all: ${NAME}

%.o: %.c ${SRCS} ${BONUS}
		${CC} ${FLAGS} -c $< -o ${<:c=o}

$(NAME): ${OBJS}
		ar crs ${NAME} ${OBJS}

bonus: ${OBJSBONUS}
		ar crs ${NAME} ${OBJSBONUS}

clean:
		make clean -C printf
		${RM} ${OBJS} ${OBJSBONUS}

fclean:	clean
		make fclean -C printf
		${RM} ${NAME}

re:		fclean all

.PHONY: fclean all bonus re clean