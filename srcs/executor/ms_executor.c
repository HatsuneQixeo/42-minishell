/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:36:33 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/28 09:33:56 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	@brief Check whether the file is executable.
	@note Print error msg accordingly if error is encountered.
 */
bool	is_executable(char *path_to_file)
{
	struct stat	file_stat;

	ft_bzero(&file_stat, sizeof(struct stat));
	if (stat(path_to_file, &file_stat) == -1)
	{
		util_perror(path_to_file, ": No such file or directory");
		return (false);
	}
	else if ((file_stat.st_mode & S_IFMT) == S_IFDIR)
	{
		util_perror(path_to_file, ": Is a directory");
		return (false);
	}
	else if ((file_stat.st_mode & S_IFMT) == S_IFREG)
	{
		if ((file_stat.st_mode & S_IXUSR) == 0)
		{
			util_perror(path_to_file, ": Permission denied");
			return (false);
		}
	}
	return (true);
}

// haven't handle builtin commands
void	execute_token_literal(t_token *token)
{
	char	**cmd_line;
	char	*absolute_path;

	cmd_line = token->value;
	absolute_path = absolute_path_find(cmd_line[0]);
	if (absolute_path && is_executable(absolute_path))
	{
		run_process_literal(absolute_path, cmd_line);
		free(absolute_path);
	}
	else if (is_executable(cmd_line[0]))
		run_process_literal(cmd_line[0], cmd_line);
}

// void	handle_redir_right(char *file_name)
// {
// 	int	fd;

// 	fd = open(file_name, O_CREAT | O_REDWR | O_TRUNC, 0644);

// }

// void	run_process_redir()
// {
// 	pid_t	pid;
// 	int		child_status;

// 	child_status = 0;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(fd, redir_fd);
// 		close(fd);
		//handle_exec_cmd()...
// 		//exit(errno)...
// 		exit();
// 	}
// 	else
// 		wait(&child_status);
// }

// void	handle_redir_right(t_node *ast_root)
// {
// 	// if (ast_root->left && )

// }

// void	execute_token_redir(t_node *ast_root)
// {
// 	int		fd;
// 	t_token	*token;

// 	token = ast_root->content;
// 	if (token->type == GREAT)
// 		handle_redir_right();
// 	// else if (token->type == DGREAT)
// 		// handle_redir_right_double();
// 	// run_process_redir();
// }

void	ms_executor(t_node *ast_root)
{
	t_token	*token;

	if (!ast_root)
		return ;
	token = ast_root->content;
	if (token->type == LITERAL)
		execute_token_literal(token);
	// else if (token_is_redir(token))
		// execute_token_redir(ast_root);
}
