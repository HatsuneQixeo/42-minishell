/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 05:39:49 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 21:26:58 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_interrupt_signal(int status)
{
	return (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT);
}

void	heredoc_handle_delimiter(char *delimiter)
{
	if (delimiter)
		free(delimiter);
	else
		ft_putstr_fd("warning: heredoc delimited by end-of-file\n", 2);
}

/* 
	@brief Read user input and store it in a tmp file.
 */
void	heredoc_read_input_to_file(char *delimiter, char *tmp_file_name)
{
	char	*line;
	int		tmp_file_fd;

	tmp_file_fd = open(tmp_file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line || util_is_same_str(delimiter, line))
			break ;
		ft_putendl_fd(line, tmp_file_fd);
		free(line);
	}
	heredoc_handle_delimiter(line);
	close(tmp_file_fd);
}

/* 
	@brief Run heredoc process.
	@note Print a newline character if process is terminated by signal.
 */
void	heredoc_process(char *delimiter, char *tmp_filename)
{
	pid_t	pid;
	int		child_status;

	pid = fork();
	if (pid == 0)
	{
		//
		signal_handler_heredoc();
		heredoc_read_input_to_file(delimiter, tmp_filename);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		//
		signal_ignore_quit_int();
		waitpid(pid, &child_status, 0);
		if (is_interrupt_signal(child_status))
			ft_putchar_fd('\n', STDOUT_FILENO);
		//
		signal_handler_parent_process();
	}
}

/* 
	@brief Read and store user input in tmp file.
	@note heredoc_node->data will be replaced with tmp_filename.
 */
int	execute_heredoc(t_ast *heredoc_node)
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
