#include "minishell.h"

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

static void	show_lstctrl_showexe(t_list *lst_exe, int padding)
{
	const char	*name = lstiter_tokenname(NULL);
	char		*padded_name;

	padded_name = ft_strmodify(ft_strjoin, ft_strcreate(' ', (padding + 1) * 4), name);
	lstiter_tokenname(padded_name);
	ft_lstiter(lst_exe, lstiter_showtoken);
	free(padded_name);
	lstiter_tokenname(name);
	ft_printf("\n");
}

static void	show_lstctrl_core(t_list *lst_ctrl, int padding)
{
	int			i;

	i = 0;
	while (lst_ctrl != NULL)
	{
		t_ctrl	*node = lst_ctrl->content;

		lst_ctrl = lst_ctrl->next;
		ft_printf("%*sctrl[%d]: %s\n"DEF, padding * 4, "",
				i, ctrl_name(node->condition));
		if (node->ft_exe == exe_argv) 
			show_lstctrl_showexe(node->lst_exe, padding);
		else if (node->ft_exe == exe_subsh)
			show_lstctrl_core(node->lst_exe, padding + 1);
		else
			ft_dprintf(2, "show_lstctrl: Unknown ft in ft_exe: %p\n", node->ft_exe);
		show_lstctrl_showexe(node->lst_rdrt, padding);
		i++;
	}
}

void	show_lstctrl(t_list *lst_ctrl)
{
	ft_printf("showing lst_ctrl\n");
	show_lstctrl_core(lst_ctrl, 0);
}
