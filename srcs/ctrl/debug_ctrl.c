/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/27 16:12:49 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctrl.h"

const char	*ctrl_name(t_ftctrl condition)
{
	if (condition == ctrl_continue)
		return (GREY"?? ctrl_continue");
	else if (condition == ctrl_success)
		return (GREEN"&& ctrl_success");
	else if (condition == ctrl_failure)
		return (RED"|| ctrl_failure");
	else
		return ("undefined function");
}

static void	pad_debuglst(t_list *lst_args, int padding,
			t_ftsetname ft_setname, t_ftiterlst ft_debug)
{
	char	*padded_name;

	padded_name = ft_strmodify(ft_strjoin,
			ft_strcreate(' ', (padding + 1) * 4), ft_setname(NULL));
	lstshow_tmpname(lst_args, ft_setname, padded_name, ft_debug);
	free(padded_name);
	ft_putchar_fd('\n', 2);
}

static void	show_lstctrl_core(t_list *lst_ctrl, int padding)
{
	t_ctrl	*ctrl;
	int		i;

	i = 0;
	while (lst_ctrl != NULL)
	{
		ctrl = lst_ctrl->content;
		ft_dprintf(2, "%*sctrl[%d]: %s\n"DEF, padding * 4, "",
			i, ctrl_name(ctrl->condition));
		if (ctrl->ft_exe == exe_argv)
			pad_debuglst(ctrl->lst_args, padding,
				lstname_token, lstshow_token);
		else if (ctrl->ft_exe == exe_subsh)
			show_lstctrl_core(ctrl->lst_args, padding + 1);
		else
			ft_dprintf(2, "show_lstctrl: Unknown ft in ft_exe: %p\n",
				ctrl->ft_exe);
		pad_debuglst(ctrl->lst_rdrt, padding,
			lstname_rdrt, lstshow_rdrt);
		lst_ctrl = lst_ctrl->next;
		i++;
	}
}

void	show_lstctrl(t_list *lst_ctrl)
{
	ft_dprintf(2, "showing lst_ctrl\n");
	show_lstctrl_core(lst_ctrl, 0);
}
