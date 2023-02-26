/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 18:26:22 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretor.h"

void	interpretation(t_data *data, t_list *lst_exe)
{
	t_ctrl	*ctrl;

	ctrl = lst_exe->content;
	if (!ctrl->condition())
		return ;
	else if (lst_exe->next != NULL)
		execute_pipe(data, lst_exe);
	else
		g_lastexit = ctrl->ft_exe(data, ctrl->lst_args, ctrl->lst_rdrt);
	debug_errno("interpretation end");
}

t_list	*interpret_getlstpipe(t_list **lst_ctrl)
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

/**
 * @brief
 * (echo $MIKU && (echo is && echo cute) || echo $MIKU is cute) | tr [:lower:] [:upper:]
 * echo $MIKU | (echo cat1 && cat && (echo cat2 && cat))
 * 
 * @param envp 
 * @param lst_ctrl 
 */
void	ms_interpretor(t_data *data, t_list **lst_ctrl)
{
	t_list	*lst_exe;

	while ((*lst_ctrl) != NULL)
	{
		lst_exe = interpret_getlstpipe(lst_ctrl);
		interpretation(data, lst_exe);
		if (!access(HEREDOC_TXT, F_OK))
			unlink(HEREDOC_TXT);
		ft_lstclear(&lst_exe, del_ctrl);
	}
}
