/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 02:24:56 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/08 09:34:09 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
    @brief Check for pattern [ '<<' <file_name> ]
 */
t_ast	*redir_in_pattern_1_heredoc(t_scanner *s)
{
	char	*file_name;
	t_ast	*parent_node;

	parent_node = NULL;
	if (s_token_type_matches(DLESS, s))
	{
		s_next(s);
		if (s_token_type_matches(LITERAL, s))
		{
			file_name = ft_strdup(s_get_token(s)->value);
			parent_node = ft_calloc(1, sizeof(t_ast));
			ast_settype(parent_node, AST_RD_HDOC);
			ast_setdata(parent_node, file_name);
			s_next(s);
			return (parent_node);
		}
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ '<' <file_name> ]
 */
t_ast	*redir_in_pattern_2_infile(t_scanner *s)
{
	char	*file_name;
	t_ast	*parent_node;

	parent_node = NULL;
	if (s_token_type_matches(LESS, s))
	{
		s_next(s);
		if (s_token_type_matches(LITERAL, s))
		{
			file_name = ft_strdup(s_get_token(s)->value);
			parent_node = ft_calloc(1, sizeof(t_ast));
			ast_settype(parent_node, AST_RD_INFILE);
			ast_setdata(parent_node, file_name);
			s_next(s);
			return (parent_node);
		}
	}
	return (NULL);
}

/*
	@return Return an array of functions that
	@return check for redir in matching pattern.
    @note Must search the patterns in the following order.
 */
t_ast *(**redir_in_pattern_array(void))(t_scanner *)
{
	static t_ast *(*pattern_func[])(t_scanner *) = {
		redir_in_pattern_1_heredoc,
		redir_in_pattern_2_infile,
		NULL
	};

return (pattern_func);

}

/* 
	@return t_ast * is returned upon success, else return NULL.
 */
t_ast	*parse_redir_in(t_scanner *s)
{
	return (pattern_searcher(redir_in_pattern_array(), s));
}
