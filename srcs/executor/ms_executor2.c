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
			close(pipe_fd[1]);
		}
		else if (pipe_stage == 2)
		 	child_process(pipe_node);
	}
	close(pipe_fd[1]);
	if (pipe_node->right && ast_gettype(pipe_node->right) == AST_PIPE)
		execute_pipe(pipe_node->right, 1, pipe_fd[0]);
	else if (pipe_node->right && ast_gettype(pipe_node->right) == AST_CMD)
		execute_pipe(pipe_node->right, 2, pipe_fd[0]);
	close(pipe_fd[0]);
	waitpid(-1, NULL, 0);
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


void	read_input_to_file(char *delimiter, char *tmp_file_name)
{
	char	*line;
	int		tmp_file_fd;

	tmp_file_fd = open(tmp_file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (util_is_same_str(delimiter, line))
			break ;
		ft_putstr_fd(line, tmp_file_fd);
		ft_putstr_fd("\n", tmp_file_fd);
		free(line);
	}
	free(line);
	close(tmp_file_fd);
}

void	signal_handler_heredoc()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sig_parent(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler_parent_process()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sig_parent);
}

void	signal_ignore()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_process(char *delimiter, char *tmp_filename)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal_handler_heredoc();
		read_input_to_file(delimiter, tmp_filename);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		signal_ignore();
		waitpid(pid, NULL, 0);
		// signal_handler_parent_process();
	}
}

int		execute_heredoc(t_ast *heredoc_node)
{
	char	*delimiter;
	char	*tmp_filename;

	if (!heredoc_node)
		return (ERROR);
	delimiter = heredoc_node->data;
	tmp_filename = tmp_filename_generator();
	heredoc_process(delimiter, tmp_filename);
	heredoc_node->data = tmp_filename;
	return (SUCCESS);
}

bool	heredoc_in_cmd(t_ast *cmd_node)
{
	t_ast	*redir_node;

	redir_node = cmd_node->left;
	while (redir_node)
	{
		if (ast_gettype(redir_node) & AST_RD_HDOC)	
		{
			if (execute_heredoc(redir_node) == SUCCESS)
				return (true);
		}
		redir_node = redir_node->left;
	}
	return (false);
}

bool	heredoc_in_pipe(t_ast *pipe_node)
{
	t_ast	*job_node;

	if (heredoc_in_cmd(pipe_node->left))
		return (true);
	job_node = pipe_node->right;	
	while (job_node && ast_gettype(job_node) == AST_PIPE)
	{
		if (heredoc_in_cmd(job_node->left))
			return (true);
		job_node = job_node->right;
	}
	if (heredoc_in_cmd(job_node))
		return (true);
	return (false);
}

bool	heredoc_in_job(t_ast *job_node)
{
	if (!job_node)
		return (false);
	if (ast_gettype(job_node) == AST_PIPE)
	{
		if (heredoc_in_pipe(job_node))
			return (true);
	}
	else if (heredoc_in_cmd(job_node))
		return (true);
	return (false);
}

bool	heredoc_in_and_or(t_ast *and_or_node)
{
	int	node_type;

	if (!and_or_node)
		return (false);
	node_type = ast_gettype(and_or_node);
	if (node_type == AST_AND  || node_type == AST_OR || node_type == AST_SEQ)
	{
		if (heredoc_in_and_or(and_or_node->left) || heredoc_in_and_or(and_or_node->right))
			return (true);
	}
	else if (heredoc_in_job(and_or_node))
		return (true);
	return (false);
}

bool	heredoc_in_cmdline(t_ast *root)
{
	if (!root)
		return (false);
	if (ast_gettype(root) == AST_SEQ)
	{
		if (heredoc_in_and_or(root->left) || heredoc_in_cmdline(root->right))
			return (true);
	}
	else
	{
		if (heredoc_in_and_or(root))
			return (true);
	}
	return (false);
}

bool	handle_heredoc(t_ast *root)
{
	return (heredoc_in_cmdline(root));
}

void	ms_executor_prototype(t_ast *root)
{
	// printf("%d\n",handle_heredoc(root));
	handle_heredoc(root);
	execute_cmdline(root);
}