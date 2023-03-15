/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:42 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTRL_H
# define CTRL_H

# include "ms_common.h"
# include "token.h"
# include "lexer.h"
# include "rdrt.h"

/* Exit Status */
typedef int	(*t_ftctrl)(void);
int			ctrl_continue(void);
int			ctrl_success(void);
int			ctrl_failure(void);

typedef int	(*t_ftexe)(t_data *data, t_list *lst_args, t_list *lst_rdrt);
int			exe_argv(t_data *data, t_list *lst_args, t_list *lst_rdrt);
int			exe_subsh(t_data *data, t_list *lst_args, t_list *lst_rdrt);

typedef struct s_control
{
	t_ftctrl	condition;
	t_ftexe		ft_exe;
	t_ftdel		exedel_ft;
	t_list		*lst_args;
	t_list		*lst_rdrt;
}			t_ctrl;

t_ctrl		*ctrl_new(t_ftctrl condition, t_ftexe exe, t_ftdel ft_del);
void		del_ctrl(void *content);

t_ftctrl	ctrl_getft(const char *value);
const char	*ctrl_getvalue(t_ftctrl ft_ctrl);

/* Debug ctrl */
void		show_lstctrl(t_list *lst_ctrl);

#endif
