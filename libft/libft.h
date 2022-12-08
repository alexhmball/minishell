/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:19:34 by aball             #+#    #+#             */
/*   Updated: 2022/12/08 20:56:36 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "printf/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

// typedef struct s_dlist
// {
// 	void			*content;
// 	struct s_dlist	*next;
// 	struct s_dlist	*prev;
// }				t_dlist;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MANDATORY~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *s1, const void *s2, size_t n);
void		*ft_memmove(void *s1, const void *s2, size_t len);
void		*ft_memset(void *b, int c, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t ln);
char		*ft_strrchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		*ft_itoa(int nbr);
char		**ft_split(char const *s, char c);
char		*ft_strtrim(char const *s1, char const *set);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~BONUS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MY FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

char		*str_sep(int size, char **strs, char *sep);
void		ft_swap(void *a, void *b);
long long	ft_atol(const char *str);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~DOUBLY LINKED LISTS~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// void	ft_lstdelone_db(t_dlist **head, t_dlist *node, void (*del)(void *));
// void	ft_lstiter_db(t_dlist *lst, void (*f)(void *));
// void	ft_lstclear_db(t_dlist **lst, void (*del)(void *));
// int	ft_lstsize_db(t_dlist *lst);
// t_dlist	*ft_lstnew_db(void *content);
// void	ft_lstadd_back_db(t_dlist **lst, t_dlist *new);
// t_dlist	*ft_lstlast_db(t_dlist *lst);
// void	ft_lstadd_front_db(t_dlist **lst, t_dlist *new);

#endif
