/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exectrl_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/11 23:21:25 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	pipe_process(t_data *data, t_ctrl *ctrl, pid_t *pid)
{
	int	fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		ms_perror("pipe_process pipe");
	*pid = fork();
	if (*pid == -1)
		ms_perror("pipe_process fork");
	else if (*pid == 0)
	{
		close(fd_pipe[READ_END]);
		ft_dup3(fd_pipe[WRITE_END], 1);
		exit(ctrl->ft_exe(data, ctrl->lst_args, ctrl->lst_rdrt));
	}
	else
		close(fd_pipe[WRITE_END]);
	return (fd_pipe[READ_END]);
}

static void	pipe_connection(t_data *data, t_list *lst_exe, pid_t *arr_pid)
{
	t_ctrl	*ctrl;
	int		fd_stdin;

	fd_stdin = dup(0);
	while (lst_exe->next != NULL)
	{
		ft_dup3(pipe_process(data, lst_exe->content, arr_pid++), 0);
		lst_exe = lst_exe->next;
	}
	ctrl = lst_exe->content;
	g_lastexit = ctrl->ft_exe(data, ctrl->lst_args, ctrl->lst_rdrt);
	ft_dup3(fd_stdin, 0);
}

static void	pipe_wait(pid_t *begin, pid_t *end)
{
	while (begin != end)
		waitpid(*begin++, NULL, 0);
}

void	exectrl_piping(t_data *data, t_list *lst_exe)
{
	pid_t		*arr_pid;
	const int	size = ft_lstsize(lst_exe) - 1;

	arr_pid = malloc(sizeof(pid_t) * size);
	if (arr_pid == NULL)
		return ;
	pipe_connection(data, lst_exe, arr_pid);
	pipe_wait(arr_pid, arr_pid + size);
	debug_errno("exectrl_piping end");
	free(arr_pid);
}
