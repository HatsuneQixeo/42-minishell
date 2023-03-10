/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:43:14 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/10 09:45:18 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	@brief Check for pattern [ '(' <command> ')' '|' <job> ]
 */
t_ast	*job_pattern_1_subshell_pipe(t_parser *p)
{
	t_ast		*cmd_node;
	t_ast		*job_node;
	t_ast		*parent_node;

	if (s_match_and_consume_token(OPEN_PAREN, p->scanner))
	{
		cmd_node = parse_cmd(p);
		if (cmd_node)
		{
			if (s_match_and_consume_token(CLOSE_PAREN, p->scanner)
				&& s_match_and_consume_token(PIPELINE, p->scanner))
			{
				job_node = parse_job(p);
				if (job_node)
				{
					parent_node = ft_calloc(1, sizeof(t_ast));
					ast_settype(parent_node, AST_PIPE);
					ast_attach(parent_node, cmd_node, job_node);
					return (parent_node);
				}
			}
			ast_free(&cmd_node);
		}
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ <command> '|' <job> ]
 */
//bug
t_ast	*job_pattern_2_cmd_pipe(t_parser *p)
{
	t_ast		*cmd_node;
	t_ast		*job_node;
	t_ast		*parent_node;

	cmd_node = parse_cmd(p);
	if (cmd_node)
	{
		if (s_match_and_consume_token(PIPELINE, p->scanner))
		{
			job_node = parse_job(p);
			if (job_node)
			{
				parent_node = ft_calloc(1, sizeof(t_ast));
				ast_settype(parent_node, AST_PIPE);
				ast_attach(parent_node, cmd_node, job_node);
				return (parent_node);
			}
		}
		ast_free(&cmd_node);
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ '(' <command> ')' ]
 */
t_ast	*job_pattern_3_subshell(t_parser *p)
{
	t_ast	*cmd_node;

	if (s_match_and_consume_token(OPEN_PAREN, p->scanner))
	{
		cmd_node = parse_cmd(p);
		if (cmd_node)
		{
			if (s_match_and_consume_token(CLOSE_PAREN, p->scanner))
				return (cmd_node);
			else
				ast_free(&cmd_node);
		}
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ <command> ]
 */
t_ast	*job_pattern_4_cmd(t_parser *p)
{
	return (parse_cmd(p));
}

/* 
	@return t_ast * is returned upon success, else return NULL.
 */
t_ast	*parse_job(t_parser *p)
{
	static t_ast	*(*job_pattern_funcs[])(t_parser *) = {
		job_pattern_1_subshell_pipe,
		job_pattern_2_cmd_pipe,
		job_pattern_3_subshell,
		job_pattern_4_cmd,
		NULL
	};

	return (pattern_searcher(job_pattern_funcs, p));
}
