/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokenlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 08:59:51 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/09 11:43:34 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*node_init(t_asttype node_type)
{
	t_ast	*node;

    node = ft_calloc(1, sizeof(t_ast));
	ast_settype(node, node_type);
	return (node);
}
/* 
	@brief Check for pattern [ <cmd_name> <token_list> ]
 */
t_ast	*tokenlist_pattern_1_cmd_name(t_sh *sh)
{
	t_scanner	*s;
	char		*cmd_name;

	s = sh->scanner;
    if (!sh->cmd_ast)
		sh->cmd_ast = node_init(AST_CMD);
	if (!sh->cmd_ast->data)
	{
		if (s_token_type_matches(LITERAL, s))
		{
			cmd_name = ft_strdup(s_get_token(s)->value);
			ast_setdata(sh->cmd_ast, cmd_name);
			s_next(s);
			parse_tokenlist(sh);
			return (sh->cmd_ast);
		}
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ <redir> <token_list> ]
 */
t_ast	*tokenlist_pattern_2_redir(t_sh *sh)
{
	t_ast		*redir_node;

	redir_node = parse_redir(sh);
	if (redir_node)
	{
		parse_tokenlist(sh);
		cmd_ast_insert_left(sh->cmd_ast, redir_node);
		return (redir_node);
	}
	return (NULL);
}

// uses global cmd_ast
/* 
	@brief Check for pattern [ <token_literal> <token_list> ]
 */
t_ast	*tokenlist_pattern_3_args(t_sh *sh)
{
	t_scanner	*s;
	char		*arg;
	t_ast		*arg_node;

	s = sh->scanner;
	if (s_token_type_matches(LITERAL, s))
	{
		arg = ft_strdup(s_get_token(s)->value);
		arg_node = ft_calloc(1, sizeof(t_ast));
		ast_settype(arg_node, AST_ARG);
		ast_setdata(arg_node, arg);
		s_next(s);
		parse_tokenlist(sh);
		cmd_ast_insert_right(sh->cmd_ast, arg_node);
		return (arg_node);
	}
	return (NULL);
}

/*
	@return Return an array of functions that check for
	tokenlist matching pattern.
	@note Must search the patterns in the following order.
 */
t_ast *(**tokenlist_pattern_array(void))(t_sh *)
{
	static t_ast *(*pattern_func[])(t_sh *) = {
		tokenlist_pattern_1_cmd_name,
		tokenlist_pattern_2_redir,
		tokenlist_pattern_3_args,
		NULL
	};

return (pattern_func);

}

/* 
	@brief Parse tokenlist.
	@return t_ast * is returned upon success, else return NULL.
 */
t_ast	*parse_tokenlist(t_sh *sh)
{
	return (pattern_searcher(tokenlist_pattern_array(), sh));
}
