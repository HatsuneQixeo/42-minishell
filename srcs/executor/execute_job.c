/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_job.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 04:46:13 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 12:04:23 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	@Execute job node.
 */
void	execute_job(t_ast *job_node)
{
	if (ast_gettype(job_node) == AST_PIPE)
		execute_pipe(job_node, PIPE_STAGE_1, STDIN_FILENO);
	else
		execute_cmd(job_node);
}
