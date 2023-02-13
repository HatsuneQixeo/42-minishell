/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_double_linked_list.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:03:25 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/12 10:25:40 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_DOUBLE_LINKED_LIST_H
# define MS_DOUBLE_LINKED_LIST_H

# include <stdlib.h>

typedef struct	s_double_list
{
	void					*content;
	struct s_double_list	*prev;
	struct s_double_list	*next;
}	t_double_list;

t_double_list   *double_lstnew(void *content);
int				double_lstsize(t_double_list *lst);
t_double_list	*double_lstlast(t_double_list *lst);
void			double_lstiter(t_double_list *lst, void (*fj)(void *));
void			double_lstadd_back(t_double_list **lst, t_double_list *new);
void			double_lstdelone(t_double_list *lst, void (*del)(void *));
void			double_lstclear(t_double_list **lst, void (*del)(void *));
#endif