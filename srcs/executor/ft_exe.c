/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:26:22 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:40 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "executor.h"

static int	redirect(char **envp, t_list *lst_rdrt)
{
	t_rdrt	*rdrt;

	while (lst_rdrt != NULL)
	{
		rdrt = lst_rdrt->content;
		if (rdrt->ft_rdrt(envp, rdrt) == -1)
			return (1);
		lst_rdrt = lst_rdrt->next;
	}
	return (0);
}

static int	argv_lstargs(t_data *data, t_list *lst_args)
{
	char	**argv;
	int		status;

	if (lst_args == NULL)
		return (0);
	argv = expand_lst_argv(data->envp, lst_args);
	status = execution(data, argv);
	ft_strlistclear(argv);
	return (status);
}

int	exe_argv(t_data *data, t_list *lst_args, t_list *lst_rdrt)
{
	int		fd_std[2];
	int		status;

	fd_std[0] = dup(0);
	fd_std[1] = dup(1);
	if (fd_std[0] == -1 || fd_std[1] == -1)
	{
		ms_perror("exe_argv: fd_std");
		close(fd_std[0]);
		close(fd_std[1]);
		return (831);
	}
	status = redirect(data->envp, lst_rdrt);
	if (status == 0)
		status = argv_lstargs(data, lst_args);
	if ((ft_dup3(fd_std[0], 0) == -1) + (ft_dup3(fd_std[1], 1) == -1))
		return (831);
	leakcheck("exe_argv");
	return (status);
}

int	exe_subsh(t_data *data, t_list *lst_args, t_list *lst_rdrt)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		ms_perror("exe_subsh");
		return (-1);
	}
	else if (pid == 0)
	{
		if (redirect(data->envp, lst_rdrt) == -1)
			exit(1);
		ms_executor(data, &lst_args);
		leakcheck("exe_subsh");
		exit(g_lastexit);
	}
	else
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
