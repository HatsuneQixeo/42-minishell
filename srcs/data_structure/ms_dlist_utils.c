/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dlist_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:03:01 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/21 01:43:34 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_double_linked_list.h"

t_double_list	*double_lstnew(void *content)
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
