/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/07 15:22:16 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctrl.h"

t_ctrl	*ctrl_new(t_ftctrl condition, t_ftexe exe, t_ftdel exedel_ft)
{
	t_ctrl	*ctrl;

	ctrl = malloc(sizeof(t_ctrl));
	if (ctrl == NULL)
		return (NULL);
	ctrl->condition = condition;
	ctrl->ft_exe = exe;
	ctrl->exedel_ft = exedel_ft;
	ctrl->lst_args = NULL;
	ctrl->lst_rdrt = NULL;
	return (ctrl);
}

void	del_ctrl(void *content)
{
	t_ctrl	*process;

	process = content;
	ft_lstclear(&process->lst_rdrt, del_rdrt);
	ft_lstclear(&process->lst_args, process->exedel_ft);
	free(process);
}
