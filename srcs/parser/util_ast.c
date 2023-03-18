/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:39:39 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 09:26:48 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	@brief Attach node at cmd_ast->right.
 */
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

/* 
	@brief Attach node at cmd_ast->left.
 */
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

/* 
	@brief Attach new and_or_node at the top.
	@note new and_or_node->left will be attach
	at previous ast_root->right.
 */
void	and_or_ast_insert_top(t_ast **ast_root, t_ast *and_or_node)
{
	if (!ast_root || !and_or_node)
		return ;
	if (!*ast_root)
		*ast_root = and_or_node;
	else
	{
		(*ast_root)->right = and_or_node->left;
		and_or_node->left = *ast_root;
		*ast_root = and_or_node;
	}
}

/* 
	@brief Attach last job node at and_or_ast_root->right.
 */
void	and_or_ast_attach_last(t_ast **ast_root, t_ast *job_node)
{
	if (!ast_root || !job_node)
		return ;
	if (!*ast_root)
		*ast_root = job_node;
	else
		(*ast_root)->right = job_node;
}
