/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:39:39 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/10 16:50:27 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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