/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_ast2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:44:14 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/10 11:02:20 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ast_settype(t_ast *node, t_asttype type)
{
	if (!node)
		return ;
	node->type = type;
}

void	ast_setdata(t_ast *node, char *data)
{
	if (!node || !data)
		return ;
	node->data = data;
	node->type |= AST_DATA;
}

void	ast_attach(t_ast *root, t_ast *left, t_ast *right)
{
	if (!root)
		return ;
	root->left = left;
	root->right = right;
}

void	ast_delete(t_ast **node)
{
	if (!*node)
		return ;
	if ((*node)->type & AST_DATA)
		free((*node)->data);
	ast_delete(&(*node)->left);
	ast_delete(&(*node)->right);
	free(*node);
	*node = NULL;
}
