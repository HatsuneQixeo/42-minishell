/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokenlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 08:59:51 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/09 20:36:09 by ntan-wan         ###   ########.fr       */
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
t_ast	*tokenlist_pattern_1_cmd_name(t_parser *p)
{
	char		*cmd_name;

	if (!p->cmd_ast->data)
	{
		if (s_token_type_matches(LITERAL, p->scanner))
		{
			cmd_name = ft_strdup(s_get_token(p->scanner)->value);
			ast_setdata(p->cmd_ast, cmd_name);
			s_next(p->scanner);
			parse_tokenlist(p);
			return (p->cmd_ast);
		}
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ <redir> <token_list> ]
 */
t_ast	*tokenlist_pattern_2_redir(t_parser *p)
{
	t_ast		*redir_node;

	redir_node = parse_redir(p);
	if (redir_node)
	{
		parse_tokenlist(p);
		cmd_ast_insert_left(p->cmd_ast, redir_node);
		return (redir_node);
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ <token_literal> <token_list> ]
 */
t_ast	*tokenlist_pattern_3_args(t_parser *p)
{
	char		*arg;
	t_ast		*arg_node;

	if (s_token_type_matches(LITERAL, p->scanner))
	{
		arg = ft_strdup(s_get_token(p->scanner)->value);
		arg_node = node_init(AST_ARG);
		ast_setdata(arg_node, arg);
		s_next(p->scanner);
		parse_tokenlist(p);
		cmd_ast_insert_right(p->cmd_ast, arg_node);
		return (arg_node);
	}
	return (NULL);
}

/* 
	@return t_ast * is returned upon success, else return NULL.
	@note Pass array of tokenlist pattern functions to pattern_searcher()
	@note for finding matching pattern.
 */
t_ast	*parse_tokenlist(t_parser *p)
{
	static t_ast	*(*tokenlist_pattern_funcs[])(t_parser *) = {
		tokenlist_pattern_1_cmd_name,
		tokenlist_pattern_2_redir,
		tokenlist_pattern_3_args,
		NULL
	};

	return (pattern_searcher(tokenlist_pattern_funcs, p));
}
