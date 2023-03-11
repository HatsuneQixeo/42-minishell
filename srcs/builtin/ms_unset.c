/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/11 23:21:25 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_common.h"

static int	valid_identifier(const char *str)
{
	if (!(ft_isalpha(*str) || *str == '_'))
		return (0);
	while (ft_isnameletter(*str))
		str++;
	return (*str == '\0');
}

static void	unset(char **envp, const char *arg)
{
	char	**env;

	env = env_getaddress(envp, arg);
	if (env == NULL)
		return ;
	free(*env);
	ft_memmove(env, env + 1, sizeof(char *) * (ft_strcount(env + 1) + 1));
}

int	ms_unset(char **argv, t_data *data)
{
	int	retval;

	retval = 0;
	while (*++argv != NULL)
	{
		if (!valid_identifier(*argv))
		{
			ms_errlog("unset: `%s': not a valid identifier\n", *argv);
			retval = 1;
		}
		else
			unset(data->envp, *argv);
	}
	return (retval);
}
