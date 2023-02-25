/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:21:06 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretor.h"

pid_t	pipe_process(t_data *data, t_ctrl *ctrl, int infd, int outfd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ms_perror("pipe_process");
	else if (pid == 0)
	{
		if ((ft_dup3(infd, 0) == -1) + (ft_dup3(outfd, 1) == -1))
			exit(1);
		ctrl->ft_exe(data, ctrl->lst_args, ctrl->lst_rdrt);
		close(0);
		close(1);
		ft_dprintf(2, "child[%s]: exitting\n", ((t_token *)ctrl->lst_args->content)->value);
		exit(g_lastexit);
	}
	else
		ft_dprintf(2, "pid[%s]: %d\n", ((t_token *)ctrl->lst_args->content)->value, pid);
	return (pid);
}

void	piping(t_data *data, t_list *lst_exe, pid_t *arr_pid)
{
	int		prev_read;
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		ms_perror("pipe");
	*arr_pid++ = pipe_process(data, lst_exe->content, 0, fd_pipe[WRITE_END]);
	close(fd_pipe[WRITE_END]);
	prev_read = fd_pipe[READ_END];
	lst_exe = lst_exe->next;
	while (lst_exe->next != NULL)
	{
		if (pipe(fd_pipe) == -1)
			ms_perror("pipe");
		*arr_pid++ = pipe_process(data, lst_exe->content, prev_read, fd_pipe[WRITE_END]);
		close(prev_read);
		close(fd_pipe[WRITE_END]);
		prev_read = fd_pipe[READ_END];
		lst_exe = lst_exe->next;
	}
	*arr_pid++ = pipe_process(data, lst_exe->content, prev_read, 1);
	close(prev_read);
}

void	execute_pipe(t_data *data, t_list *lst_exe)
{
	pid_t		*arr_pid;
	const int	size = ft_lstsize(lst_exe);
	int			status;

	arr_pid = malloc(sizeof(pid_t) * size);
	if (arr_pid == NULL)
		return ;
	piping(data, lst_exe, arr_pid);
	for (int i = 0; i < size; i++)
	{
		ft_printf("%d: pipeexit\n", waitpid(arr_pid[i], &status, 0));
		g_lastexit = WEXITSTATUS(status);
	}
	free(arr_pid);
}
