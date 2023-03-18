/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:15:49 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 13:26:19 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	g_exit_status_update(int child_status)
{
	if (WIFEXITED(child_status))
		g_exit_status = WEXITSTATUS(child_status);
	else if (WIFSIGNALED(child_status))
		g_exit_status = 128 + WTERMSIG(child_status);
	// print_err_msg...
}

void	cmd_child_process(t_ast *cmd_node)
{
	char	**argv;
	char	*cmd_path;
	char	**envp_arr;

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
			cmd_child_free(cmd_node, cmd_path, argv, envp_arr);
			exit(EXIT_SUCCESS);
		}
	}
	cmd_child_free(cmd_node, cmd_path, argv, envp_arr);
	exit(EXIT_FAILURE);
}

/* 
    @brief Wait all childs process to terminate.
    @note This is to prevent zombie process from occuring.
 */
void	cmd_parent_process(pid_t child_pid)
{
	int	pid;
	int	child_status;

	while (true)
	{
		pid = waitpid(-1, &child_status, 0);
		if (pid <= 0)
			break ;
		else if (pid == child_pid)
			g_exit_status_update(child_status);
	}
}

void	cmd_child_free(t_ast *cmd, char *cmd_path, char **argv, char **envp)
{
	t_double_list	*envp_list;

	envp_list = envp_get();
	if (cmd_path)
		free(cmd_path);
	ast_delete(&cmd);
	envp_free(&envp_list);
	util_arr_str_free(argv);
	util_arr_str_free(envp);
}

void	execute_cmd(t_ast *cmd_node)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		cmd_child_process(cmd_node);
	else if (pid > 0)
		cmd_parent_process(pid);
}
