/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:15:15 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 12:02:57 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	@brief Execute the pipe according to pipe_stage.
	@param pipe_stage pipe_stage_1 handles pipe_node->left,
	pipe_stage_2 handles pipe_node->right.
 */
void	execute_pipe_stage(t_ast *pipe_node, int pipe_stage, int write_end_fd)
{
	if (pipe_stage == PIPE_STAGE_1)
	{
		dup2(write_end_fd, STDOUT_FILENO);
		cmd_child_process(pipe_node->left);
	}
	else if (pipe_stage == PIPE_STAGE_2)
		cmd_child_process(pipe_node);
}

/* 
	@brief Execute pipe_node->right.
	@param Read_end_fd read_end_fd of the previous pipe.
	@note If pipe_node->right is another pipe tree, calls
	execute_pipe() recursively.
 */
void	execute_pipe_node_right(t_ast *pipe_node, int read_end_fd)
{
	int	node_type;

	if (pipe_node->right)
	{
		node_type = ast_gettype(pipe_node->right);
		if (node_type == AST_PIPE)
			execute_pipe(pipe_node->right, PIPE_STAGE_1, read_end_fd);
		else if (node_type == AST_CMD)
			execute_pipe(pipe_node->right, PIPE_STAGE_2, read_end_fd);
	}
}

/* 
	@brief Execute pipe recursively.
	@param pipe_stage pipe_stage_1 handles pipe_node->left,
	pipe_stage_2 handles pipe_node->right.
	@param read_end_fd read_end_fd of the previous pipe.
*/
void	execute_pipe(t_ast *pipe_node, int pipe_stage, int read_end_fd)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (!pipe_node)
		return ;
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(read_end_fd, STDIN_FILENO);
		execute_pipe_stage(pipe_node, pipe_stage, pipe_fd[1]);
		close(pipe_fd[1]);
	}
	else
	{
		close(pipe_fd[1]);
		execute_pipe_node_right(pipe_node, pipe_fd[0]);
		close(pipe_fd[0]);
		waitpid(-1, NULL, 0);
	}
}
