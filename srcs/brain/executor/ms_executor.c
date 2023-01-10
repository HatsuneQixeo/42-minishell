/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:31:59 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 03:22:16 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	execute_cmd(char **argv)
{
	char	*path;

	path = ms_path_search(argv[0]);
	if (!path)
		return (1);
	execv(path, argv);
	free(path);
	return (0);
}

int	ms_executor(t_node *node)
{
	char	**argv;
	pid_t	pid;	

	if (!node)
		return (1);
	pid = 0;
	argv = ms_node_to_argv(node);
	pid = fork();
	if (pid == 0)
		execute_cmd(argv);
	else if (pid < 0)
	{
		printf("ms_executor: failed to fork command\n");
		return (1);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

void	ms_cmds_free(char ***argv)
{
	int		i;
	char	**av;

	i = -1;
	av = *argv;
	while (av[++i])
		free(av[i]);
	free(av);
	*argv = NULL;
}
