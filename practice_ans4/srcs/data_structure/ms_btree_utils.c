/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_btree_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:41:57 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/11 11:31:24 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_btree.h"
#include "ms_token.h"

t_node *btree_node_init(void *content)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node)
	{
		node->left = NULL;
		node->right = NULL;
		node->content = content;
	}
	return (node);
}

void    btree_node_insert(t_node **parent, t_node *node)
{
	t_token	*token;

	token = node->content;
	if (!*parent)
		*parent = node;
	else if (ms_token_is_operator(token))
	{
		node->left = *parent;
		*parent = node;
	}
	else
		btree_node_insert(&(*parent)->right, node);
}

// void	btree_of_cmds_create(t_list *token_list)
// {
// 	t_node	*root;
// 	t_list	*list;

// 	list = token_list;
// 	while (list)
// 	{
// 		root = NULL;
// 		ast_create();
// 		list = list->next;
// 	}

// }

// void	ms_parser(t_list *token_list)
// {
// 	t_list	*list;
// 	t_token	*token;

// 	list = token_list;
// 	while (list)
// 	{
// 		token = list->content;
// 		//	
// 		list = list->next;
// 	}
// 	// if (list)
// 		// ms_parser(list);
// }