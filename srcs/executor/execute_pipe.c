/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:15:15 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/17 16:10:11 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipe_stage(t_ast *pipe_node, int pipe_stage, int write_end_fd)
{
	if (pipe_stage == 1)
	{
		dup2(write_end_fd, STDOUT_FILENO);
		cmd_child_process(pipe_node->left);
	}
	else if (pipe_stage == 2)
		cmd_child_process(pipe_node);
}

void	execute_pipe_node_right(t_ast *pipe_node, int read_end_fd)
{
	int	node_type;

	if (pipe_node->right)
	{
		node_type = ast_gettype(pipe_node->right);
		if (node_type == AST_PIPE)
			execute_pipe(pipe_node->right, 1, read_end_fd);
		else if (node_type == AST_CMD)
			execute_pipe(pipe_node->right, 2, read_end_fd);
	}
}

void	pipe_child_process(t_ast *pipe_node, int pipe_stage, int pipe_fd[2], int read_end_fd)
{
	close(pipe_fd[0]);
	dup2(read_end_fd, STDIN_FILENO);
	execute_pipe_stage(pipe_node, pipe_stage, pipe_fd[1]);
	close(pipe_fd[1]);
}

void	pipe_parent_process(t_ast *pipe_node, int pipe_fd[2])
{
	close(pipe_fd[1]);
	execute_pipe_node_right(pipe_node, pipe_fd[0]);
	close(pipe_fd[0]);
	waitpid(-1, NULL, 0);
}

void	execute_pipe(t_ast *pipe_node, int pipe_stage, int read_end_fd)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (!pipe_node)
		return ;
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
		pipe_child_process(pipe_node, pipe_stage, pipe_fd, read_end_fd);
	else
		pipe_parent_process(pipe_node, pipe_fd);
	waitpid(-1, NULL, 0);
}
