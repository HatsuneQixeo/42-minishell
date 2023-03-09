/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 10:31:20 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/09 11:04:57 by ntan-wan         ###   ########.fr       */
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

int	ast_gettype(t_ast *node)
{
	return (node->type & (~AST_DATA));
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

/* ********** PARSER ********** */

t_ast	*cmd_ast(t_ast *node)
{
	static t_ast	*cmd_ast;

	if (!cmd_ast)
		cmd_ast = ft_calloc(1, sizeof(t_ast));
	if (node)
		cmd_ast = node;
	return (cmd_ast);
}



// t_ast	**and_or_ast(t_ast *node)
// {
// 	static t_ast	**and_or_ast;

// 	if (!and_or_ast)
// 		and_or_ast = ft_calloc(1, sizeof(t_ast *));
// 	if (node)
// 		*and_or_ast = node;
// 	return (and_or_ast);
// }
