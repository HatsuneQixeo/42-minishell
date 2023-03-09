/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:28:01 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/09 17:49:15 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	and_or_ast_insert_last(t_ast **ast_root, t_ast *new_node)
{
	if (!ast_root || !new_node)
		return ;
	if (!*ast_root)
		*ast_root = new_node;
	else
		(*ast_root)->right = new_node;
}

void	and_or_ast_insert(t_ast **ast_root, t_ast *new_node)
{
	if (!ast_root || !new_node)
		return ;
	if (!*ast_root)
		*ast_root = new_node;
	else
	{
		(*ast_root)->right = new_node->left;
		new_node->left = *ast_root;
		*ast_root = new_node;
	}
}

// so many side effects
// p->and_or_ast?
t_ast	*and_or_node_init(int node_type, t_ast *attach_left_node)
{
	t_ast	*and_or_node;

	and_or_node = ft_calloc(1, sizeof(t_ast));
	ast_settype(and_or_node, node_type);
	ast_attach(and_or_node, attach_left_node, NULL);
	// and_or_ast_insert(and_or_ast(NULL), and_or_node);
	return (and_or_node);
}

/* 
	@brief Check for pattern [ <job> '&&' <and_or> ]
 */
// return NULL?
t_ast	*and_or_pattern_1_and(t_parser *p)
{
	t_ast	*job_node;
	t_ast	*and_or_node;

	job_node = parse_job(p);
	//
	// print_ast(job_node, 0);
	if (job_node)
	{
		if (s_match_and_consume_token(AND, p->scanner))
		{
			// and_or_node = ft_calloc(1, sizeof(t_ast));
			// ast_settype(and_or_node, AST_AND);
			// ast_attach(and_or_node, job_node, NULL);
			and_or_node = and_or_node_init(AST_AND, job_node);
			// print_ast(and_or_node, 0);
			// and_or_ast_insert(and_or_ast(NULL), parent_node, false);
			// and_or_ast_insert(&p->and_or_ast, and_or_node);
			and_or_ast_insert(p->and_or_ast, and_or_node);
			if (parse_and_or(p))
				return (and_or_node);
			else
				return (NULL);
		}
		ast_delete(&job_node);
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ <job> '||' <and_or> ]
 */
//  return NULL?
t_ast	*and_or_pattern_2_or(t_parser *p)
{
	t_ast	*job_node;
	t_ast	*and_or_node;

	job_node = parse_job(p);
	if (job_node)
	{
		if (s_match_and_consume_token(OR, p->scanner))
		{
			// and_or_node = ft_calloc(1, sizeof(t_ast));
			// ast_settype(and_or_node, AST_OR);
			// ast_attach(and_or_node, job_node, NULL);
			and_or_node = and_or_node_init(AST_OR, job_node);
			// and_or_ast_insert(&p->and_or_ast, and_or_node);
			and_or_ast_insert(p->and_or_ast, and_or_node);
			if (parse_and_or(p))
				return (and_or_node);
			else
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
	{
		//
		// if (!p->and_or_ast)
		// 	p->and_or_ast = ft_calloc(1, sizeof(t_ast));
		// and_or_ast_insert_last(&p->and_or_ast, job_node);
		and_or_ast_insert_last(p->and_or_ast, job_node);
	}
	return (job_node);
}

/* 
	@brief Check for pattern [ '(' <command_line> ')' '&&' <and_or> ]
 */
//return NULL?
t_ast	*and_or_pattern_4_cmd_line_and(t_parser *p)
{
	t_ast	*cmdline_node;
	t_ast	*and_or_node;
	t_ast	*save;

	save = *(p->and_or_ast);
	if (s_match_and_consume_token(OPEN_PAREN, p->scanner))
	{
		//
		cmdline_node = parse_cmdline(p);
		if (cmdline_node && s_match_and_consume_token(CLOSE_PAREN, p->scanner))
		{
			if (s_match_and_consume_token(AND, p->scanner))
			{
				and_or_node = and_or_node_init(AST_AND, cmdline_node);
				// and_or_ast_insert(&p->and_or_ast, and_or_node);
				and_or_ast_insert(p->and_or_ast, and_or_node);
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
// open close bracket?
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
			if (s_match_and_consume_token(CLOSE_PAREN, p->scanner))
			{
				if (s_match_and_consume_token(OR, p->scanner))
				{
					and_or_node = and_or_node_init(AST_OR, cmd_line_node);
					and_or_ast_insert(p->and_or_ast, and_or_node);
					if (parse_and_or(p))
						return (and_or_node);
					return (NULL);
				}
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
				//
				// if (!p->and_or_ast)
					// p->and_or_ast = ft_calloc(1, sizeof(t_ast));
				// and_or_ast_insert_last(&p->and_or_ast, cmd_line_node);
				and_or_ast_insert_last(p->and_or_ast, cmd_line_node);
				// printf("sdfds\n");
				return (cmd_line_node);
			}
			ast_delete(&cmd_line_node);
		}
		*(p->and_or_ast) = save;
	}
	return (NULL);
}

/*
	@return Return an array of functions that
	@return check for and_or matching pattern.
    @note Must search the patterns in the following order.
 */
t_ast *(**and_or_pattern_array(void))(t_parser *)
{
	static t_ast *(*pattern_func[])(t_parser *) = {
		and_or_pattern_1_and,
		and_or_pattern_2_or,
		and_or_pattern_3_job,
		and_or_pattern_4_cmd_line_and,
		and_or_pattern_5_cmd_line_or,
		and_or_pattern_6_cmd_line,
		NULL
	};

return (pattern_func);

}

/* 
	@return t_ast * is returned upon success, else return NULL.
 */
t_ast	*parse_and_or(t_parser *p)
{
	return (pattern_searcher(and_or_pattern_array(), p));
}
