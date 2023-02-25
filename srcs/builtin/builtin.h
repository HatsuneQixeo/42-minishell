/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 18:26:23 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "ms_common.h"

typedef int	(*t_ftbuiltin)(char **argv, t_data *data);

int	ms_cd(char **argv, t_data *data);
int	ms_echo(char **argv, t_data *data);
int	ms_env(char **argv, t_data *data);
int	ms_exit(char **argv, t_data *data);
int	ms_export(char **argv, t_data *data);
int	ms_pwd(char **argv, t_data *data);
int	ms_unset(char **argv, t_data *data);

#endif
