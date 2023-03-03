/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/27 16:12:49 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	*ft_findcommand(char **envp, const char *command)
{
	char	*abspath_command;
	char	**strlist_path;
	int		y;

	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	strlist_path = ft_split(env_getvalue(envp, "PATH"), ':');
	if (strlist_path == NULL)
		return (NULL);
	y = -1;
	while (strlist_path[++y] != NULL)
	{
		abspath_command = ft_strmerge("%s/%s", strlist_path[y], command);
		if (!access(abspath_command, F_OK))
		{
			ft_strlistclear(strlist_path);
			return (abspath_command);
		}
		free(abspath_command);
	}
	ft_strlistclear(strlist_path);
	return (NULL);
}

static void	exec_program(char **envp, char **argv)
{
	char	*prgpath;

	prgpath = ft_findcommand(envp, argv[0]);
	if (prgpath == NULL)
		ms_errlog("%s: command not found\n", argv[0]);
	else if (ft_strchr(argv[0], '/') && access(prgpath, F_OK) == -1)
		ms_perror(argv[0]);
	else
	{
		execve(prgpath, argv, envp);
		ms_perror(prgpath);
		leakcheck(prgpath);
		exit(126);
	}
	leakcheck(argv[0]);
	exit(127);
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
		exec_program(data->envp, argv);
	else
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
