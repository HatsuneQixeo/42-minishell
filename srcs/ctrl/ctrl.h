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

typedef struct s_control	t_ctrl;
typedef int	(*t_ftexe)(t_data *data, t_ctrl *ctrl, int fd_in, int fd_out);

struct s_control
{
	t_ftctrl	condition;
	/**
	 * @brief Question:
	 * What should this ptr point to
	 * ex: Like a lst of arguments, like lst_args
	 * ex: or a subshell, how should I act is this is subsh
	 * What if this is a function take takes in a linked list?
	 * That solves it?
	 */
	t_ftexe		ft_exe;
	t_list		*lst_args;
	t_list		*lst_rdrt;
};

/* Currently only serves as an idenfitier */
int	exe_argv(t_data *data, t_ctrl *exe, int fd_in, int fd_out);
/* Currently only serves as an idenfitier */
int	exe_subsh(t_data *data, t_ctrl *subsh, int fd_in, int fd_out);

t_ftctrl	ctrl_value(const char *value);
void		del_ctrl(void *content);
t_ctrl		*ctrl_new(t_ftctrl condition, t_ftexe exe);

/* Debug ctrl */
const char	*ctrl_name(t_ftctrl condition);
void	show_lstctrl(t_list *lst_ctrl);
// void	lstshow_ctrl(int i, void *content);

#endif
