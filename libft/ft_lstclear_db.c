/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_db.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:36:16 by aball             #+#    #+#             */
/*   Updated: 2022/08/24 22:36:23 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear_db(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*clear;

	while (*lst)
	{
		clear = (*lst)->next;
		ft_lstdelone_db(lst, *lst, del);
		*lst = clear;
	}
}
