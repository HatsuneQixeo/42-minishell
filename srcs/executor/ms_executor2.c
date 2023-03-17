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

	if (!heredoc_node || ast_gettype(heredoc_node) != AST_RD_HDOC)
		return (ERROR);
	delimiter = heredoc_node->data;
	tmp_filename = tmp_filename_generator();
	heredoc_process(delimiter, tmp_filename);
	heredoc_node->data = tmp_filename;
	return (SUCCESS);
}

int	print_data(t_ast *root, int level)
{
	// printf("sdfdsf\n");
	if (!root)
		return (ERROR);
	if (level == 1 && root->type)
		printf("%d\n", ast_gettype(root));
	else if (level > 1)
	{
		print_data(root->left, level - 1);
		print_data(root->right, level - 1);
	}
	return (SUCCESS);
}

int	get_tree_height(t_ast *root)
{
	int	left_height;
	int	right_height;

	if (!root)
		return (0);
	else
	{
		left_height = get_tree_height(root->left);
		right_height = get_tree_height(root->right);
		if (left_height > right_height)
			return (left_height + 1);
		else
			return (right_height + 1);
	}
}

void	ast_tree_breadth_first_search(t_ast *root, int (*f)(t_ast *, int))
{
	int	i;
	int	tree_height;

	i = 0;
	tree_height = get_tree_height(root);
	while (++i <= tree_height)
		f(root, i);
}

void	tree_inorder_traversal(t_ast *root, int (*f)(t_ast *))
{
	if (!root)
		return ;
	tree_inorder_traversal(root->left, f);
	f(root);
	tree_inorder_traversal(root->right, f);
}

void	ms_executor_prototype(t_ast *root)
{
	tree_inorder_traversal(root, execute_heredoc);
	// ast_tree_breadth_first_search(root, print_data);
	// tree_inorder_traversal(root, execute);
	execute_cmdline(root);
}