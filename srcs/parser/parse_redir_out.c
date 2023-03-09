/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 08:38:59 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/08 15:51:06 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	@brief Check for pattern [ '>>' <file_name> ]
 */
t_ast	*redir_out_pattern_1_append(t_sh *sh)
{
	t_scanner	*s;
	char		*file_name;
	t_ast		*parent_node;

	s = sh->scanner;
	parent_node = NULL;
	if (s_token_type_matches(DGREAT, s))
	{
		s_next(s);
		if (s_token_type_matches(LITERAL, s))
		{
			file_name = ft_strdup(s_get_token(s)->value);
			parent_node = ft_calloc(1, sizeof(t_ast));
			ast_settype(parent_node, AST_RD_APPEND);
			ast_setdata(parent_node, file_name);
			s_next(s);
			return (parent_node);
		}
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ '>' <file_name> ]
 */
t_ast	*redir_out_pattern_2_outfile(t_sh *sh)
{
	t_scanner	*s;
	char		*file_name;
	t_ast		*parent_node;

	s = sh->scanner;
	parent_node = NULL;
	if (s_token_type_matches(GREAT, s))
	{
		s_next(s);
		if (s_token_type_matches(LITERAL, s))
		{
			file_name = ft_strdup(s_get_token(s)->value);
			parent_node = ft_calloc(1, sizeof(t_ast));
			ast_settype(parent_node, AST_RD_TRUNC);
			ast_setdata(parent_node, file_name);
			s_next(s);
			return (parent_node);
		}
	}
	return (NULL);
}

/*
    @note Must search the patterns in the following order.
	@return Return an array of functions that
	@return check for redir out matching pattern.
 */
t_ast *(**redir_out_pattern_array(void))(t_sh *)
{
	static t_ast *(*pattern_func[])(t_sh *) = {
		redir_out_pattern_1_append,
		redir_out_pattern_2_outfile,
		NULL
	};

return (pattern_func);

}

/* 
	@return t_ast * is returned upon success, else return NULL.
 */
t_ast	*parse_redir_out(t_sh *sh)
{
	return (pattern_searcher(redir_out_pattern_array(), sh));
}
