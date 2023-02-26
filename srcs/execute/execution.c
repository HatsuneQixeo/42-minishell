/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 18:26:22 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretor.h"

static char	*ft_findcommand(char **envp, const char *command)
{
	char	*abspath_command;
	char	**strlist_path;
	int		y;

	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	strlist_path = ft_split(ft_getenv(envp, "PATH"), ':');
	if (strlist_path == NULL)
		return (NULL);
	y = -1;
	while (strlist_path[++y] != NULL)
	{
		abspath_command = ft_strinsert(strlist_path[y], "/", command);
		if (access(abspath_command, F_OK) != -1)
		{
			ft_strlistclear(strlist_path);
			return (abspath_command);
		}
		free(abspath_command);
	}
	ft_strlistclear(strlist_path);
	return (NULL);
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
		char	*prgpath;
		prgpath = ft_findcommand(data->envp, argv[0]);
		if (prgpath == NULL)
		{
			ms_errlog("%s: command not found\n", argv[0]);
			leakcheck(argv[0]);
			exit(127);
		}
		execve(prgpath, argv, data->envp);
		ms_perror(prgpath);
		leakcheck(prgpath);
		exit(g_lastexit);
	}
	else
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
