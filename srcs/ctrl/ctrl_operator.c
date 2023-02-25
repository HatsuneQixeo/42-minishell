/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:21:06 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_common.h"

void	ms_waitall(void)
{
	int		status;
	pid_t	pid;

	while (1)
	{
		pid = wait(&status);
		if (pid == -1)
			break ;
		g_lastexit = WEXITSTATUS(status);
		ft_printf("%d exited\n", pid);
	}
}

int	ctrl_continue(void)
{
	return (1);
}

// int	ctrl_wait(void)
// {
// 	ms_waitall();
// 	return (1);
// }

int	ctrl_success(void)
{
	ms_waitall();
	return (g_lastexit == 0);
}

int	ctrl_failure(void)
{
	ms_waitall();
	return (g_lastexit != 0);
}
