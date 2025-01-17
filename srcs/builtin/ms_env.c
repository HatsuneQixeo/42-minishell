/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:39 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ms_common.h"

static void	iteri_putenv(unsigned int i, void *envp)
{
	const char	*env = ((const char **)envp)[i];

	if (!ft_strchr(env, '='))
		return ;
	ft_putendl_fd(env, 1);
}

int	ms_env(char **argv, t_data *data)
{
	ft_aaiteri(data->envp, iteri_putenv);
	return (0);
	(void)argv;
}
