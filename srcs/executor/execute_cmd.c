/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:38:57 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/17 13:15:44 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_argc_get(t_ast *cmd_node)
{
	int	count;

	count = 0;
	while (cmd_node)
	{
		count++;
		cmd_node = cmd_node->right;
	}
	return (count);
}

char	**cmd_argv_init(t_ast *cmd_node)
{
	int		i;
	int		argc;
	char	**argv;

	i = -1;
	argv = NULL;
	argc = cmd_argc_get(cmd_node);
	while (cmd_node && cmd_node->data)
	{
		if (!argv)
		{
			argv = ft_calloc(argc + 1, sizeof(char *));
			argv[argc] = NULL;
		}
		argv[++i] = ft_strdup(cmd_node->data);
		cmd_node = cmd_node->right;
	}
	return (argv);
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
		{
			if (WIFEXITED(child_status))
				g_exit_status = WEXITSTATUS(child_status);
			//WIFSIGNALED...
		}
	}
	//
	// printf("exit_status = %d\n", g_exit_status);
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