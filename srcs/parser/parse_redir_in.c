/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 02:24:56 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 07:37:11 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
    @brief Check for pattern [ '<<' <file_name> ]
 */
t_ast	*redir_in_pattern_1_heredoc(t_parser *p)
{
	char		*file_name;
	t_ast		*parent_node;

	parent_node = NULL;
	if (s_match_and_consume_token(DLESS, p->scanner))
	{
		if (s_token_type_matches(LITERAL, p->scanner))
		{
			file_name = ft_strdup(s_get_token(p->scanner)->value);
			parent_node = ft_calloc(1, sizeof(t_ast));
			ast_settype(parent_node, AST_RD_HDOC);
			ast_setdata(parent_node, file_name);
			s_next(p->scanner);
			return (parent_node);
		}
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ '<' <file_name> ]
 */
t_ast	*redir_in_pattern_2_infile(t_parser *p)
{
	char		*file_name;
	t_ast		*parent_node;

	parent_node = NULL;
	if (s_match_and_consume_token(LESS, p->scanner))
	{
		if (s_token_type_matches(LITERAL, p->scanner))
		{
			file_name = ft_strdup(s_get_token(p->scanner)->value);
			parent_node = ft_calloc(1, sizeof(t_ast));
			ast_settype(parent_node, AST_RD_INFILE);
			ast_setdata(parent_node, file_name);
			s_next(p->scanner);
			return (parent_node);
		}
	}
	return (NULL);
}

/* 
	@return t_ast * is returned upon success, else return NULL.
	@note Pass array of pattern functions to pattern_searcher()
	@note for finding matching pattern.
 */
t_ast	*parse_redir_in(t_parser *p)
{
	static t_ast	*(*redir_in_pattern_funcs[])(t_parser *) = {
		redir_in_pattern_1_heredoc,
		redir_in_pattern_2_infile,
		NULL
	};

	return (pattern_searcher(redir_in_pattern_funcs, p));
}
