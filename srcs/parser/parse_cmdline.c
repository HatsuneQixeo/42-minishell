/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:21:26 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/09 10:56:41 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	@brief Check for pattern [ <and_or> ';' <command_line> ]
 */
t_ast	*cmd_line_pattern_1_andor_cmdline(t_parser *p)
{
	t_ast	*and_or_node;
	t_ast	*cmd_line_node;
	t_ast	*seq_node;

	*(p->and_or_ast) = NULL;
	parse_and_or(p);
	and_or_node = *(p->and_or_ast);
	if (and_or_node)
	{
		if (s_match_and_consume_token(SEMICOLON, p->scanner))
		{
			cmd_line_node = parse_cmdline(p);
			if (cmd_line_node)
			{
				seq_node = ft_calloc(1, sizeof(t_ast));
				ast_settype(seq_node, AST_SEQ);
				ast_attach(seq_node, and_or_node, cmd_line_node);
				return (seq_node);
			}
		}
		ast_delete(&and_or_node);
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ <and_or> ';' ]
 */
t_ast	*cmd_line_pattern_2_andor_seq(t_parser *p)
{
	t_ast	*and_or_node;
	t_ast	*seq_node;

	*(p->and_or_ast) = NULL;
	parse_and_or(p);
	and_or_node = *(p->and_or_ast);
	if (and_or_node)
	{
		if (s_match_and_consume_token(SEMICOLON, p->scanner))
		{
			seq_node = ft_calloc(1, sizeof(t_ast));
			ast_settype(seq_node, AST_SEQ);
			ast_attach(seq_node, and_or_node, NULL);
			return (seq_node);
		}
		ast_delete(&and_or_node);
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ <and_or> ]
 */
t_ast	*cmd_line_pattern_3_andor(t_parser *p)
{
	t_ast	*and_or_node;

	*(p->and_or_ast) = NULL;
	parse_and_or(p);
	and_or_node = *(p->and_or_ast);
	return (and_or_node);
}

/* 
	@return t_ast * is returned upon success, else return NULL.
	@note Pass array of pattern functions to pattern_searcher()
	@note for finding matching pattern.
 */
t_ast	*parse_cmdline(t_parser *p)
{
	static t_ast	*(*cmdline_pattern_funcs[])(t_parser *) = {
		cmd_line_pattern_1_andor_cmdline,
		cmd_line_pattern_2_andor_seq,
		cmd_line_pattern_3_andor,
		NULL
	};

	return (pattern_searcher(cmdline_pattern_funcs, p));
}
