/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:40 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "executor.h"

static t_list	*exectrl_getlstpipe(t_list **lst_ctrl)
{
	t_list	*lst_exe;
	t_ctrl	*ctrl;

	lst_exe = ft_lstextract_front(lst_ctrl);
	while ((*lst_ctrl) != NULL)
	{
		ctrl = (*lst_ctrl)->content;
		if (ctrl->condition != ctrl_continue)
			break ;
		ft_lstadd_back(&lst_exe, ft_lstextract_front(lst_ctrl));
	}
	return (lst_exe);
}

static void	exectrl_exe(t_data *data, t_list *lst_exe)
{
	t_ctrl	*ctrl;

	ctrl = lst_exe->content;
	if (!ctrl->condition())
		return ;
	else if (lst_exe->next != NULL)
		exectrl_piping(data, lst_exe);
	else
		g_lastexit = ctrl->ft_exe(data, ctrl->lst_args, ctrl->lst_rdrt);
	debug_errno("execute end");
	if (!access(HEREDOC_TXT, F_OK))
		unlink(HEREDOC_TXT);
}

void	ms_executor(t_data *data, t_list **lst_ctrl)
{
	t_list	*lst_exe;

	while ((*lst_ctrl) != NULL)
	{
		lst_exe = exectrl_getlstpipe(lst_ctrl);
		exectrl_exe(data, lst_exe);
		ft_lstclear(&lst_exe, del_ctrl);
	}
}
