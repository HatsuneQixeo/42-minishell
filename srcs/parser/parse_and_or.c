/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:28:01 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 09:19:00 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*and_or_node_init(int node_type, t_ast *attach_left_node)
{
	t_ast	*and_or_node;

	and_or_node = ft_calloc(1, sizeof(t_ast));
	ast_settype(and_or_node, node_type);
	ast_attach(and_or_node, attach_left_node, NULL);
	return (and_or_node);
}

/* 
	@brief Check for pattern [ <job> '&&' <and_or> ]
 */
t_ast	*and_or_pattern_1_and(t_parser *p)
{
	t_ast	*job_node;
	t_ast	*and_or_node;

	job_node = parse_job(p);
	if (job_node)
	{
		if (s_match_and_consume_token(AND, p->scanner))
		{
			and_or_node = and_or_node_init(AST_AND, job_node);
			and_or_ast_insert_top(p->and_or_ast, and_or_node);
			if (parse_and_or(p))
				return (and_or_node);
			return (NULL);
		}
		ast_delete(&job_node);
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ <job> '||' <and_or> ]
 */
t_ast	*and_or_pattern_2_or(t_parser *p)
{
	t_ast	*job_node;
	t_ast	*and_or_node;

	job_node = parse_job(p);
	if (job_node)
	{
		if (s_match_and_consume_token(OR, p->scanner))
		{
			and_or_node = and_or_node_init(AST_OR, job_node);
			and_or_ast_insert_top(p->and_or_ast, and_or_node);
			if (parse_and_or(p))
				return (and_or_node);
			return (NULL);
		}
		ast_delete(&job_node);
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ <job> ]
 */
t_ast	*and_or_pattern_3_job(t_parser *p)
{
	t_ast	*job_node;

	job_node = parse_job(p);
	if (job_node)
		and_or_ast_attach_last(p->and_or_ast, job_node);
	return (job_node);
}

/* 
	@return t_ast * is returned upon success, else return NULL.
	@note Pass array of pattern functions to pattern_searcher()
	@note for finding matching pattern.
 */
t_ast	*parse_and_or(t_parser *p)
{
	static t_ast	*(*and_or_pattern_funcs[])(t_parser *) = {
		and_or_pattern_1_and,
		and_or_pattern_2_or,
		and_or_pattern_3_job,
		and_or_pattern_4_cmd_line_and,
		and_or_pattern_5_cmd_line_or,
		and_or_pattern_6_cmd_line,
		NULL
	};

	return (pattern_searcher(and_or_pattern_funcs, p));
}
