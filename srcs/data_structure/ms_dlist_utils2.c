/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dlist_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:40:41 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/22 23:42:13 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_lstdelone(t_double_list *lst, void (*del)(void *))
{
	t_double_list	*prev;
	t_double_list	*next;

	if (!lst || !del)
		return ;
	prev = lst->prev;
	next = lst->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	del(lst->content);
	free(lst);
}

void	double_lstclear(t_double_list **lst, void (*del)(void *))
{
	t_double_list	*list;
	t_double_list	*next;	

	if (!*lst || !del)
		return ;
	list = *lst;
	while (list)
	{
		next = list->next;
		double_lstdelone(list, del);
		list = next;
	}
	*lst = NULL;
}
