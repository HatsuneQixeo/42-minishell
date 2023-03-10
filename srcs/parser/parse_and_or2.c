/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:17:29 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/10 10:20:19 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	@brief Check for pattern [ '(' <command_line> ')' '&&' <and_or> ]
 */
t_ast	*and_or_pattern_4_cmd_line_and(t_parser *p)
{
	t_ast	*cmdline_node;
	t_ast	*and_or_node;
	t_ast	*save;

	save = *(p->and_or_ast);
	if (s_match_and_consume_token(OPEN_PAREN, p->scanner))
	{
		cmdline_node = parse_cmdline(p);
		if (cmdline_node)
		{
			if (s_match_and_consume_token(CLOSE_PAREN, p->scanner)
				&& s_match_and_consume_token(AND, p->scanner))
			{
				and_or_node = and_or_node_init(AST_AND, cmdline_node);
				and_or_ast_insert_top(p->and_or_ast, and_or_node);
				if (parse_and_or(p))
					return (and_or_node);
				return (NULL);
			}
			ast_delete(&cmdline_node);
		}
		*(p->and_or_ast) = save;
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ '(' <command_line> ')' '||' <and_or> ]
 */
t_ast	*and_or_pattern_5_cmd_line_or(t_parser *p)
{
	t_ast	*cmd_line_node;
	t_ast	*and_or_node;
	t_ast	*save;

	save = *(p->and_or_ast);
	if (s_match_and_consume_token(OPEN_PAREN, p->scanner))
	{
		cmd_line_node = parse_cmdline(p);
		if (cmd_line_node)
		{
			*(p->and_or_ast) = save;
			if (s_match_and_consume_token(CLOSE_PAREN, p->scanner)
				&& s_match_and_consume_token(OR, p->scanner))
			{
				and_or_node = and_or_node_init(AST_OR, cmd_line_node);
				and_or_ast_insert_top(p->and_or_ast, and_or_node);
				if (parse_and_or(p))
					return (and_or_node);
				return (NULL);
			}
			ast_delete(&cmd_line_node);
		}
		*(p->and_or_ast) = save;
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ '(' <command_line> ')' ]
 */
t_ast	*and_or_pattern_6_cmd_line(t_parser *p)
{
	t_ast	*cmd_line_node;
	t_ast	*save;

	save = *(p->and_or_ast);
	if (s_match_and_consume_token(OPEN_PAREN, p->scanner))
	{
		cmd_line_node = parse_cmdline(p);
		if (cmd_line_node)
		{
			*(p->and_or_ast) = save;
			if (s_match_and_consume_token(CLOSE_PAREN, p->scanner))
			{
				and_or_ast_insert_last(p->and_or_ast, cmd_line_node);
				return (cmd_line_node);
			}
			ast_delete(&cmd_line_node);
		}
		*(p->and_or_ast) = save;
	}
	return (NULL);
}
