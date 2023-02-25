/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:26:22 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 18:26:22 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretor.h"

int	redirection(char **envp, t_list *lst_rdrt)
{
	t_rdrt	*rdrt;

	while (lst_rdrt != NULL)
	{
		rdrt = lst_rdrt->content;
		if (rdrt->ft_rdrt(envp, rdrt) == -1)
			return (-1);
		lst_rdrt = lst_rdrt->next;
	}
	return (0);
}

int	exe_argv(t_data *data, t_list *lst_args, t_list *lst_rdrt)
{
	char	**argv;
	t_list	*lst;
	int		fd_std[2];

	if (lst_args == NULL)
		return (0);
	fd_std[0] = dup(0);
	fd_std[1] = dup(1);
	if (redirection(data->envp, lst_rdrt) == -1)
	{
		ft_dup3(fd_std[0], 0);
		ft_dup3(fd_std[1], 1);
		return (-1);
	}
	lst = ms_expander(data->envp, lst_args, expand_lst_argv);
	argv = (char **)ft_lsttoaa_clear(&lst);
	g_lastexit = execution(data, argv);
	ft_strlistclear(argv);
	if ((ft_dup3(fd_std[0], 0) == -1) + (ft_dup3(fd_std[1], 1) == -1))
		return (-1);
	return (0);
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
		if (redirection(data->envp, lst_rdrt) == -1)
			exit(1);
		ms_interpretor(data, &lst_args);
		leakcheck("exe_subsh");
		exit(g_lastexit);
	}
	else
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
