/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:21:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "ms_common.h"
# include "expander.h"
# include "builtin.h"
# include "ctrl.h"

int		exec_builtin(t_data *data, char **argv);
int		execution(t_data *data, char **argv);

void	ms_interpretor(t_data *data, t_list **lst_ctrl);

#endif
