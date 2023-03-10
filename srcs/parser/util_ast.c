/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:39:39 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/10 09:45:41 by ntan-wan         ###   ########.fr       */
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

void	cmd_ast_insert_right(t_ast *root, t_ast *node)
{
	t_ast	*tmp;

	if (!root || !node)
		return ;
	tmp = root->right;
	root->right = node;	
	node->right = tmp;
	node->left = NULL;
}

void	cmd_ast_insert_left(t_ast *root, t_ast *node)
{
	t_ast	*tmp;

	if (!root || !node)
		return ;
	tmp = root->left;
	root->left = node;	
	node->left = tmp;
	node->right = NULL;
}

void	and_or_ast_insert_top(t_ast **ast_root, t_ast *new_node)
{
	if (!ast_root || !new_node)
		return ;
	if (!*ast_root)
		*ast_root = new_node;
	else
	{
		(*ast_root)->right = new_node->left;
		new_node->left = *ast_root;
		*ast_root = new_node;
	}
}

void	and_or_ast_insert_last(t_ast **ast_root, t_ast *new_node)
{
	if (!ast_root || !new_node)
		return ;
	if (!*ast_root)
		*ast_root = new_node;
	else
		(*ast_root)->right = new_node;
}

void	ast_free(t_ast **node)
{
	if (!*node)
		return ;
	if ((*node)->type & AST_DATA)
		free((*node)->data);
	ast_free(&(*node)->left);
	ast_free(&(*node)->right);
	free(*node);
	*node = NULL;
}