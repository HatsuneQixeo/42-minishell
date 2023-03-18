/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 04:48:18 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 11:55:03 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_conditional_operator(t_ast *node)
{
	int	type;

	type = ast_gettype(node);
	return (type == AST_AND || type == AST_OR || type == AST_SEQ);
}

bool	is_right_exit_status(t_ast *node)
{
	int	node_type;

	node_type = ast_gettype(node);
	if (node_type == AST_AND)
		return (g_exit_status == 0);
	else if (node_type == AST_OR)
		return (g_exit_status != 0);
	else
		return (true);
}

/* 
	@brief Execute and_or_node.
 */
void	execute_and_or(t_ast *and_or_node)
{
	if (!and_or_node)
		return ;
	else if (is_conditional_operator(and_or_node))
	{
		execute_and_or(and_or_node->left);
		if (is_right_exit_status(and_or_node))
			execute_and_or(and_or_node->right);
	}
	else
		execute_job(and_or_node);
}
