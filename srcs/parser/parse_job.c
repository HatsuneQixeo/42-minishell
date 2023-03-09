/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:43:14 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/08 22:33:58 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	@brief Check for pattern [ '(' <command> ')' '|' <job> ]
 */
t_ast	*job_pattern_1_subshell_pipe(t_sh *sh)
{
	t_ast		*cmd_node;
	t_ast		*job_node;
	t_ast		*parent_node;

	if (s_match_and_consume_token(OPEN_PAREN, sh->scanner))
	{
		cmd_node = parse_cmd(sh);
		if (cmd_node && s_match_and_consume_token(CLOSE_PAREN, sh->scanner))
		{
			if (s_match_and_consume_token(PIPELINE, sh->scanner))
			{
				job_node = parse_job(sh);
				if (job_node)
				{
					parent_node = ft_calloc(1, sizeof(t_ast));
					ast_settype(parent_node, AST_PIPE);
					ast_attach(parent_node, cmd_node, job_node);
					return (parent_node);
				}
			}
			ast_delete(&cmd_node);
		}
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ <command> '|' <job> ]
 */
t_ast	*job_pattern_2_cmd_pipe(t_sh *sh)
{
	t_ast		*cmd_node;
	t_ast		*job_node;
	t_ast		*parent_node;

	cmd_node = parse_cmd(sh);
	if (cmd_node)
	{
		if (s_match_and_consume_token(PIPELINE, sh->scanner))
		{
			job_node = parse_job(sh);
			if (job_node)
			{
				parent_node = ft_calloc(1, sizeof(t_ast));
				ast_settype(parent_node, AST_PIPE);
				ast_attach(parent_node, cmd_node, job_node);
				return (parent_node);
			}
		}
		ast_delete(&cmd_node);
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ '(' <command> ')' ]
 */
t_ast	*job_pattern_3_subshell(t_sh *sh)
{
	t_ast	*cmd_node;

	if (s_match_and_consume_token(OPEN_PAREN, sh->scanner))
	{
		cmd_node = parse_cmd(sh);
		if (cmd_node)
		{
			if (s_match_and_consume_token(CLOSE_PAREN, sh->scanner))
				return (cmd_node);
			else
				ast_delete(&cmd_node);
		}
	}
	return (NULL);
}

/* 
	@brief Check for pattern [ <command> ]
 */
t_ast	*job_pattern_4_cmd(t_sh *sh)
{
	return (parse_cmd(sh));
}

/*
	@return Return an array of functions that
	@return check for redir in matching pattern.
    @note Must search the patterns in the following order.
 */
t_ast *(**job_pattern_array(void))(t_sh *)
{
	static t_ast *(*pattern_func[])(t_sh *) = {
		job_pattern_1_subshell_pipe,
		job_pattern_2_cmd_pipe,
		job_pattern_3_subshell,
		job_pattern_4_cmd,
		NULL
	};

return (pattern_func);

}

/* 
	@return t_ast * is returned upon success, else return NULL.
 */
t_ast	*parse_job(t_sh *sh)
{
	return (pattern_searcher(job_pattern_array(), sh));
}
