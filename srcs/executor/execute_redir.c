/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:19:02 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 14:07:29 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redir_fd_out(int redir_type, char *file_name)
{
	int	fd;

	if (redir_type & AST_RD_TRUNC)
		fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (redir_type & AST_RD_APPEND)
		fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		perror(file_name);
	return (fd);
}

int	get_redir_fd_in(int redir_type, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (redir_type & AST_RD_HDOC)
		unlink(file_name);
	if (fd == -1)
		perror(file_name);
	return (fd);
}

/* 
	@brief Get the 2 fd that is to be redirected to.
	@param redir_fd The fd will be stored in redir_fd[0]
	and redir_fd[1].
	@return Return SUCCESS if successful, else return ERROR.
 */
int	get_redir_fd(t_ast *redir, int redir_fd[2])
{
	int	redir_type;

	redir_type = ast_gettype(redir);
	if (redir_type & AST_RD_INFILE || redir_type & AST_RD_HDOC)
	{
		if (redir_fd[STDIN_FILENO] >= 0)
			close(redir_fd[STDIN_FILENO]);
		redir_fd[STDIN_FILENO] = get_redir_fd_in(redir_type, redir->data);
	}
	else if (redir_type & AST_RD_TRUNC || redir_type & AST_RD_APPEND)
	{
		if (redir_fd[STDOUT_FILENO] >= 0)
			close(redir_fd[STDOUT_FILENO]);
		redir_fd[STDOUT_FILENO] = get_redir_fd_out(redir_type, redir->data);
	}
	return (redir_fd[STDIN_FILENO] == -1 || redir_fd[STDOUT_FILENO] == -1);
}

/* 
	@brief Execute_redir_node.
 */
int	execute_redir(t_ast *redir_node)
{
	int	redir_fd[2];

	redir_fd[STDIN_FILENO] = -2;
	redir_fd[STDOUT_FILENO] = -2;
	while (redir_node)
	{
		if (get_redir_fd(redir_node, redir_fd) == ERROR)
			return (ERROR);
		redir_node = redir_node->left;
	}
	if (redir_fd[STDIN_FILENO] >= 0)
	{
		dup2(redir_fd[STDIN_FILENO], STDIN_FILENO);
		close(redir_fd[STDIN_FILENO]);
	}
	if (redir_fd[STDOUT_FILENO] >= 0)
	{
		dup2(redir_fd[STDOUT_FILENO], STDOUT_FILENO);
		close(redir_fd[STDOUT_FILENO]);
	}
	return (SUCCESS);
}
