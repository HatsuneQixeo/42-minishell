#ifndef CTRL_H
# define CTRL_H

# include "ms_common.h"
# include "rdrt.h"
# include "token.h"

typedef int	(*t_ftctrl)(void);

/* Exit Status */
int		ctrl_continue(void);
int		ctrl_wait(void); /* Semicolon, not part of the subject; Not implemented just yet */
int		ctrl_success(void);
int		ctrl_failure(void);

typedef int	(*t_ftexe)(t_data *data, t_list *lst, int fd_in, int fd_out);

/* Currently only serves as an idenfitier */
int	exe_argv(t_data *data, t_list *lst_argv, int fd_in, int fd_out);
/* Currently only serves as an idenfitier */
int	exe_subsh(t_data *data, t_list *lst_ctrl, int fd_in, int fd_out);
typedef struct s_control
{
	t_ftctrl	condition;
	/**
	 * @brief Question:
	 * What should this ptr point to
	 * ex: Like a lst of arguments, like lst_exe
	 * ex: or a subshell, how should I act is this is subsh
	 * What if this is a function take takes in a linked list?
	 * That solves it?
	 */
	t_ftexe			ft_exe;
	t_list			*lst_exe;
	t_list			*lst_rdrt;
}			t_ctrl;

t_ftctrl	ctrl_value(const char *value);
void		del_ctrl(void *content);
t_ctrl		*ctrl_new(t_ftctrl condition, t_ftexe exe);

/* Debug ctrl */
const char	*ctrl_name(t_ftctrl condition);
void	show_lstctrl(t_list *lst_ctrl);
// void	lstshow_ctrl(int i, void *content);

#endif
