/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor_prototype.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:15:54 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/13 06:28:58 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redir_out(int redir_type, char *file_name)
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

int	handle_redir_in(int redir_type, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	// haven't handle error handling unlink...
	if (redir_type & AST_RD_HDOC)
		unlink(file_name);
	if (fd == -1)
		perror(file_name);
	return (fd);
}

void	redir_fd_get(t_ast *redir, int redir_fd[2])
{
	int	redir_type;
	
	redir_type = ast_gettype(redir);
	if (redir_type & AST_RD_INFILE || redir_type & AST_RD_HDOC)
	{
		if (redir_fd[STDIN_FILENO] >= 0)
			close(redir_fd[STDIN_FILENO]);
		redir_fd[STDIN_FILENO] = handle_redir_in(redir_type, redir->data);
	}
	else if (redir_type & AST_RD_TRUNC || redir_type & AST_RD_APPEND)
	{
		if (redir_fd[STDOUT_FILENO] >= 0)
			close(redir_fd[STDOUT_FILENO]);
		redir_fd[STDOUT_FILENO] = handle_redir_out(redir_type, redir->data);
	}
}

int	execute_redir(t_ast *redir_node)
{
	int	redir_fd[2];

	redir_fd[STDIN_FILENO] = -2;
	redir_fd[STDOUT_FILENO] = -2;
	while (redir_node)
	{
		redir_fd_get(redir_node, redir_fd);
		if (redir_fd[STDIN_FILENO] == -1 || redir_fd[STDOUT_FILENO] == -1)
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

int	cmd_count_args(t_ast *cmd_node)
{
	int	count;
	int	node_type;

	count = 0;
	while (cmd_node)	
	{
		node_type = ast_gettype(cmd_node);
		if (node_type == AST_CMD || node_type == AST_ARG)	
			count++;
		else
			break ;
		cmd_node = cmd_node->right;
	}
	return (count);
}

char	**cmd_argv_init(t_ast *cmd_node)
{
	int		i;
	int		argc;
	char	**argv;
	int		node_type;

	if (!cmd_node || !cmd_node->data)
		return (NULL);
	i = -1;
	argc = cmd_count_args(cmd_node);
	argv = ft_calloc(argc + 1, sizeof(char *));
	while (cmd_node)
	{
		node_type = ast_gettype(cmd_node);
		if (node_type == AST_CMD || node_type == AST_ARG)	
		 	argv[++i] = ft_strdup(cmd_node->data);
		else
			break ;
		cmd_node = cmd_node->right;
	}
	argv[argc] = NULL;
	return (argv);
}

// t_cmd	*cmd_init(t_ast *cmd_node)
// {
// 	t_cmd	*cmd;

// 	if (!cmd_node || ast_gettype(cmd_node) != AST_CMD)
// 		return (NULL);
// 	cmd = ft_calloc(1, sizeof(t_cmd));
// 	cmd->argc = cmd_count_args(cmd_node);
// 	cmd->argv = cmd_argv_init(cmd_node);
// 	return (cmd);
// }

void	child_free(t_ast *cmd, char *cmd_path, char **argv, char **envp)
{
	t_double_list	*envp_list;

	envp_list = envp_get();
	if (cmd_path)
		free(cmd_path);
	envp_free(&envp_list);
	ast_delete(&cmd);
	util_arr_str_free(argv);
	util_arr_str_free(envp);
}

void	child_process(t_ast *cmd_node)
{
	char			**argv;
	char			*cmd_path;
	char			**envp_arr;

	cmd_path = NULL;
	envp_arr = util_list_to_arr_str(envp_get());
	argv = cmd_argv_init(cmd_node);
	if (argv)
		cmd_path = absolute_path_find(argv[0]);
	if (execute_redir(cmd_node->left) == SUCCESS)
	{
		if (cmd_path && is_executable(cmd_path))
			execve(cmd_path, argv, envp_arr);
		else if (!argv)
		{
			child_free(cmd_node, cmd_path, argv, envp_arr);
			exit(EXIT_SUCCESS);
		}
	}
	child_free(cmd_node, cmd_path, argv, envp_arr);
	exit(EXIT_FAILURE);
}

void	parent_process(pid_t child_pid)
{
	int	pid;
	int	child_status;

	while (true)
	{
		pid = waitpid(-1, &child_status, 0);
		if (pid <= 0)
			break ;
		else if (pid == child_pid)
		{
			if (WIFEXITED(child_status))
				g_exit_status = WEXITSTATUS(child_status);
			//WIFSIGNALED...
		}
	}
	//
	// printf("exit_status = %d\n", g_exit_status);
}

pid_t	execute_processes(t_ast *cmd_node)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		child_process(cmd_node);
	else if (pid > 0)
		parent_process(pid);
}

void	execute_cmd(t_ast *cmd_node)
{
	// t_cmd	*cmd;

	// cmd = cmd_init(cmd_node);
	// if (!cmd_node->data)
		// execute_empty_cmd(cmd_node);

	execute_processes(cmd_node);
}

void	execution_wait(void)
{
	pid_t	pid;
	int		status;

	while (true)
	{
		pid = waitpid(-1, &status, 0);
		if (pid <= 0)
			break ;
	}
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
	{
		dup2(read_end_fd, STDIN_FILENO);
		close(pipe_fd[0]);
		if (pipe_stage == 1)
		{
			dup2(pipe_fd[1], STDOUT_FILENO);
			child_process(pipe_node->left);
		}
		else if (pipe_stage == 2)
		 	child_process(pipe_node);
	}
	close(pipe_fd[1]);
	waitpid(-1, NULL, 0);
	if (pipe_node->right && ast_gettype(pipe_node->right) == AST_PIPE)
		execute_pipe(pipe_node->right, 1, pipe_fd[0]);
	else if (pipe_node->right && ast_gettype(pipe_node->right) == AST_CMD)
		execute_pipe(pipe_node->right, 2, pipe_fd[0]);
}

void	execute_job(t_ast *job_node)
{
	if (ast_gettype(job_node) == AST_PIPE)
		execute_pipe(job_node, 1, 0);
	else
		execute_cmd(job_node);
}

void	execute_and_or(t_ast *and_or_node)
{
	int	root_type;

	if (!and_or_node)
		return ;
	root_type = ast_gettype(and_or_node);
	if (root_type == AST_AND)
	{
		execute_and_or(and_or_node->left);
		if (g_exit_status == 0)
			execute_and_or(and_or_node->right);
	}
	else if (root_type == AST_OR)
	{
		execute_and_or(and_or_node->left);
		if (g_exit_status != 0)
			execute_and_or(and_or_node->right);
	}
	else if (root_type == AST_SEQ)
	{
		execute_and_or(and_or_node->left);
		execute_and_or(and_or_node->right);
	}
	else
		execute_job(and_or_node);
}

void	execute_cmdline(t_ast *cmdline_node)
{
	if (!cmdline_node)
		return ;
	if (ast_gettype(cmdline_node) == AST_SEQ)
	{
		execute_and_or(cmdline_node->left);
		execute_cmdline(cmdline_node->right);
	}
	else
		execute_and_or(cmdline_node);
}

void	ms_executor_prototype(t_ast *root)
{
	execute_cmdline(root);
}