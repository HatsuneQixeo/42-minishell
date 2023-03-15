/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:05 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:40 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

typedef struct s_builtinlst
{
	const char	*name;
	t_ftbuiltin	ft;
}		t_builtinlst[];

int	exec_builtin(t_data *data, char **argv)
{
	int							exe_amt;
	static const t_builtinlst	builtinlst = {
	{"cd", ms_cd},
	{"echo", ms_echo},
	{"pwd", ms_pwd},
	{"export", ms_export},
	{"unset", ms_unset},
	{"env", ms_env},
	{"exit", ms_exit}
	};

	exe_amt = (sizeof(builtinlst) / sizeof(builtinlst[0]));
	while (exe_amt--)
	{
		if (!ft_strcmp(argv[0], builtinlst[exe_amt].name))
			return (builtinlst[exe_amt].ft(argv, data));
	}
	return (-1);
}
