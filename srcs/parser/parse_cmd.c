/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:04:45 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/09 11:39:08 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
    @brief Check for pattern [ <token_list> ]
 */
t_ast   *cmd_pattern_1_tokenlist(t_sh *sh)
{
    // sh->cmd_ast = ft_calloc(1, sizeof(t_ast));
	// node = ft_calloc(1, sizeof(t_ast));
	// ast_settype(sh->cmd_ast, AST_CMD);
	// cmd_ast(node);
	parse_tokenlist(sh);
    if (!sh->cmd_ast->data)
    {
        free(sh->cmd_ast);
        sh->cmd_ast = NULL;
    }
    return (sh->cmd_ast);

	// if (node != NULL && node->data == NULL && node->left == NULL && node->right == NULL)
	// {
	// 	free(node);
	// 	return (NULL);
	// }
}

/* 
	@return t_ast * is returned upon success, else return NULL.
 */
t_ast	*parse_cmd(t_sh *sh)
{
	return (cmd_pattern_1_tokenlist(sh));
}