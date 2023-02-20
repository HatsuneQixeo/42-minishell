#include "minishell.h"

const char	*ctrl_name(t_ftexitstatus condition)
{
	if (condition == ctrl_any)
		return ("??: ctrl_any");
	else if (condition == ctrl_success)
		return ("&&: ctrl_success");
	else if (condition == ctrl_failure)
		return ("||: ctrl_failure");
	else
		return ("undefined function");
}

static void	show_ctrl_showexe(t_list *lst_exe, int padding)
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

static void	show_ctrl_core(t_list *lst_ctrl, int padding)
{
	int	i;

	i = 0;
	while (lst_ctrl != NULL)
	{
		t_ctrl	*node = lst_ctrl->content;

		lst_ctrl = lst_ctrl->next;
		ft_printf("%*sctrl[%d]: %s\n", padding * 4, "", i, ctrl_name(node->condition));
		if (node->ft_exe == exe_argv) 
			show_ctrl_showexe(node->lst_exe, padding);
		else if (node->ft_exe == exe_subsh)
			show_ctrl_core(node->lst_exe, padding + 1);
		else
			ft_dprintf(2, "Show_ctrl: Unknown ft in ft_exe: %p\n", node->ft_exe);
		i++;
	}
}

void	show_ctrl(t_list *lst_ctrl)
{
	show_ctrl_core(lst_ctrl, 0);
}
