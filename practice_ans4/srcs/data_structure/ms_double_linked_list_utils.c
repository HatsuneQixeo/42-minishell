/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_double_linked_list_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:03:01 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/12 10:24:16 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_double_linked_list.h"

t_double_list   *double_lstnew(void *content)
{
	t_double_list	*new;

	new = malloc(sizeof(t_double_list));
	if (new)
	{
		new->content = content;
		new->prev = NULL;
		new->next = NULL;
	}
	return (new);
}

t_double_list	*double_lstlast(t_double_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	double_lstadd_back(t_double_list **lst, t_double_list *new)
{
	t_double_list	*last;
	
	if (!new)
		return ;
	else if (*lst)
	{
		last = double_lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
	else
		*lst = new;
}

void	double_lstdelone(t_double_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

void	double_lstclear(t_double_list **lst, void (*del)(void *))
{
	t_double_list	*list;
	t_double_list	*next;	

	list = *lst;
	while (list)
	{
		next = list->next;
		double_lstdelone(list, del);
		list = next;
	}
	*lst = NULL;
}

void	double_lstiter(t_double_list *lst, void (*f)(void *))
{
	if (!lst || !f)	
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

int	double_lstsize(t_double_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}