/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 18:26:23 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETOR_H
# define INTERPRETOR_H

# include "ms_common.h"
# include "ctrl.h"
# include "expander.h"
# include "builtin.h"


int		exec_builtin(t_data *data, char **argv);
int		execution(t_data *data, char **argv);
void	execute_pipe(t_data *data, t_list *lst_exe);

void	ms_interpretor(t_data *data, t_list **lst_ctrl);

#endif
