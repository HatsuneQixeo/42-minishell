/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:04:45 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 07:38:22 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	@brief Check for pattern [ <token_list> ]
 */
t_ast	*cmd_pattern_1_tokenlist(t_parser *p)
{
	t_ast	*cmd_node;

	cmd_node = node_init(AST_CMD);
	p->cmd_ast = cmd_node;
	parse_tokenlist(p);
	if (cmd_node->data || p->cmd_ast->left || p->cmd_ast->right)
		return (cmd_node);
	else
	{
		free(cmd_node);
		return (NULL);
	}
}

/* 
	@return t_ast * is returned upon success, else return NULL.
	@note Pass array of pattern functions to pattern_searcher()
	@note for finding matching pattern.
 */
t_ast	*parse_cmd(t_parser *p)
{
	return (cmd_pattern_1_tokenlist(p));
}
