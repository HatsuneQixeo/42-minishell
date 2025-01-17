/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:40 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ms_common.h"
#include "signal.h"

int	ms_exit(char **argv, t_data *data)
{
	const char	*arg = argv[1];
	int			nbr;

	if (isatty(1))
		ft_putendl_fd("exit", 2);
	termios_ctrl(TERMSHOW);
	if (arg == NULL)
		exit(g_lastexit);
	else if (!stris_numeric(arg))
	{
		ms_errlog("exit: %s: numeric argument required\n", arg);
		exit(255);
	}
	else if (argv[2] != NULL)
		ms_errlog("exit: too many arguments\n");
	else
	{
		ft_atoi(arg, &nbr);
		exit(nbr);
	}
	return (1);
	(void)data;
}
