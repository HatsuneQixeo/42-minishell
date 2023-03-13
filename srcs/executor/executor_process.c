/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:28:19 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/12 18:22:07 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	@brief Internally it runs execve() function.
 */
void	run_child_process_literal(char *path_name, char **cmd_line)
{
	char			**envp;
	// t_double_list	*env_list;
	int				status;

	// env_list = envp_set_or_get(NULL);
	envp = util_list_to_arr_str(envp_get());
	status = execve(path_name, cmd_line, envp);
	exit(status);
}

/* 
	@brief Wait for child process to terminate.
 */
void	run_parent_process_literal(void)
{
	int	child_status;

	child_status = 0;
	wait(&child_status);
	// if (WIFSIGNALED())...WTERMSIG()...
	// if (WIFEXITED())...
	// WEXITSTATUS()...
}

void	run_process_literal(char *path_name, char **cmd_line)
{
	pid_t			pid;

	pid = fork();
	if (pid == 0)
		run_child_process_literal(path_name, cmd_line);
	else
		run_parent_process_literal();
}
