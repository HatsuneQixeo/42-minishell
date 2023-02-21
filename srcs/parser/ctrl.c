#include "minishell.h"

void	del_ctrl(void *content)
{
	t_ctrl	*process;

	process = content;
	if (process->ft_exe == exe_argv)
		ft_lstclear(&process->lst_exe, del_token);
	else if (process->ft_exe == exe_subsh)
		ft_lstclear(&process->lst_exe, del_ctrl);
	else
		ft_dprintf(2, "del_ctrl does not recognize the ft_exe: %p\n", process->ft_exe);
	ft_lstclear(&process->lst_rdrt, del_token);
	free(process);
}

t_ctrl	*ctrl_new(t_ftexitstatus condition, t_ftexe exe)
{
	t_ctrl	*ctrl;

	ctrl = malloc(sizeof(t_ctrl));
	if (ctrl == NULL)
		return (NULL);
	ctrl->condition = condition;
	ctrl->ft_exe = exe;
	ctrl->lst_exe = NULL;
	ctrl->lst_rdrt = NULL;
	return (ctrl);
}
