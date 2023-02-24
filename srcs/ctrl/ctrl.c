#include "minishell.h"

t_ftctrl	ctrl_value(const char *value)
{
	if (!ft_strcmp(value, "&&"))
		return (ctrl_success);
	else if (!ft_strcmp(value, "||"))
		return (ctrl_failure);
	else if (!ft_strcmp(value, "|"))
		return (ctrl_continue);
	ft_dprintf(2, "ctrl_value does not recognize: %s\n", value);
	return (NULL);
}

t_ctrl	*ctrl_new(t_ftctrl condition, t_ftexe exe)
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

void	del_ctrl(void *content)
{
	t_ctrl	*process;

	process = content;
	ft_lstclear(&process->lst_rdrt, del_rdrt);
	if (process->ft_exe == exe_argv)
		ft_lstclear(&process->lst_exe, del_token);
	else if (process->ft_exe == exe_subsh)
		ft_lstclear(&process->lst_exe, del_ctrl);
	else
		ft_dprintf(2, "del_ctrl does not recognize the ft_exe: %p\n", process->ft_exe);
	free(process);
}
