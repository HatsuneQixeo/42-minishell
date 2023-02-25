/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:21:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTRL_H
# define CTRL_H

# include "ms_common.h"
# include "token.h"
# include "rdrt.h"


/* Exit Status */
int			ctrl_continue(void);
/* Semicolon, not part of the subject; Not implemented just yet */
int			ctrl_wait(void);
int			ctrl_success(void);
int			ctrl_failure(void);

typedef int	(*t_ftctrl)(void);
typedef int	(*t_ftexe)(t_data *data, t_list *lst_args, t_list *lst_rdrt);

typedef struct s_control
{
	t_ftctrl	condition;
	t_ftexe		ft_exe;
	t_list		*lst_args;
	t_list		*lst_rdrt;
}			t_ctrl;

int			exe_argv(t_data *data, t_list *lst_args, t_list *lst_rdrt);
int			exe_subsh(t_data *data, t_list *lst_args, t_list *lst_rdrt);

t_ftctrl	ctrl_value(const char *value);
void		del_ctrl(void *content);
t_ctrl		*ctrl_new(t_ftctrl condition, t_ftexe exe);

/* Debug ctrl */
const char	*ctrl_name(t_ftctrl condition);
void		show_lstctrl(t_list *lst_ctrl);
// void	lstshow_ctrl(int i, void *content);

#endif
