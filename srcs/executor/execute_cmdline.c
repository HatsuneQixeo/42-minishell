/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 05:37:48 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 13:27:22 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmdline(t_ast *cmdline_node)
{
	if (!cmdline_node)
		return ;
	if (ast_gettype(cmdline_node) == AST_SEQ)
	{
		execute_and_or(cmdline_node->left);
		execute_cmdline(cmdline_node->right);
	}
	else
		execute_and_or(cmdline_node);
}
