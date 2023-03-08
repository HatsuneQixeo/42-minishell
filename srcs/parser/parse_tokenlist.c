/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokenlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 08:59:51 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/08 09:57:25 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// uses global cmd_ast
/* 
	@brief Check for pattern [ <cmd_name> <token_list> ]
 */
t_ast	*tokenlist_pattern_1_cmd_name(t_scanner *s)
{
	char	*cmd_name;

	if (cmd_ast(NULL)->data == NULL)
	{
		if (s_token_type_matches(LITERAL, s))
		{
			cmd_name = ft_strdup(s_get_token(s)->value);
			ast_setdata(cmd_ast(NULL), cmd_name);
			s_next(s);
			parse_tokenlist(s);
			return (cmd_ast(NULL));
		}
	}
	return (NULL);
}

// uses global cmd_ast
/* 
	@brief Check for pattern [ <redir> <token_list> ]
 */
t_ast	*tokenlist_pattern_2_redir(t_scanner *s)
{
	t_ast	*redir_node;

	redir_node = parse_redir(s);
	if (redir_node)
	{
		parse_tokenlist(s);
		cmd_ast_insert_left(cmd_ast(NULL), redir_node);
		return (redir_node);
	}
	return (NULL);
}

// uses global cmd_ast
/* 
	@brief Check for pattern [ <token_literal> <token_list> ]
 */
t_ast	*tokenlist_pattern_3_args(t_scanner *s)
{
	char	*arg;
	t_ast	*node;

	if (s_token_type_matches(LITERAL, s))
	{
		arg = ft_strdup(s_get_token(s)->value);
		node = ft_calloc(1, sizeof(t_ast));
		ast_settype(node, AST_ARG);
		ast_setdata(node, arg);
		s_next(s);
		parse_tokenlist(s);
		cmd_ast_insert_right(cmd_ast(NULL), node);
		return (node);
	}
	return (NULL);
}

/*
	@note Must search the patterns in the following order.
	@return Return an array of functions that
	@return check for tokenlist matching pattern.
 */
t_ast *(**tokenlist_pattern_array(void))(t_scanner *)
{
	static t_ast *(*pattern_func[])(t_scanner *) = {
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
t_ast	*parse_tokenlist(t_scanner *s)
{
	return (pattern_searcher(tokenlist_pattern_array(), s));
}
