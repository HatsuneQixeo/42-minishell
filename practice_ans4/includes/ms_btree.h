/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:41:28 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/13 13:34:56 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BTREE_H
# define MS_BTREE_H

typedef struct	s_node
{
	void			*content;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

t_node *btree_node_init(void *content);
void    btree_node_add(t_node **parent, t_node *node);
#endif