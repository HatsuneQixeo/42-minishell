/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:21:06 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretor.h"

static void	ft_pathaccess(char **envp, char **ptr_executable)
{
	char	*joined;
	char	**strlist_path;
	int		y;

	y = -1;
	strlist_path = ft_split(ft_getenv(envp, "PATH"), ':');
	if (strlist_path == NULL)
		return ;
	while (strlist_path[++y] != NULL)
	{
		joined = ft_strinsert(strlist_path[y], "/", *ptr_executable);
		if (access(joined, F_OK | X_OK) != -1) /* Accurate error message? */
		{
			free(*ptr_executable);
			*ptr_executable = joined;
			break ;
		}
		free(joined);
	}
	ft_strlistclear(strlist_path);
}

int	execution(t_data *data, char **argv)
{
	pid_t	pid;
	int		status;

	status = exec_builtin(data, argv);
	if (status != -1)
		return (status);
	pid = fork();
	if (pid == -1)
		ms_perror("execution");
	else if (pid == 0)
	{
		ft_pathaccess(data->envp, argv);
		execve(*argv, argv, data->envp);
		ms_errlog("%s: command not found\n", *argv);
		exit(127);
	}
	else
		waitpid(pid, &status, 0);
	ft_dprintf(2, "execution: %s: exited\n", argv[0]);
	return (WEXITSTATUS(status));
}
