/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:22:17 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:42 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_common.h"

char	**env_getaddress(char **envp, const char *varname)
{
	return ((char **)ft_aafind((void **)envp, varname, cmp_strvarname));
}

char	*env_getvalue(char **envp, const char *varname)
{
	char	**env;

	env = env_getaddress(envp, varname);
	if (env == NULL || !ft_strchr(*env, '='))
		return (NULL);
	else
		return (&(*env)[ft_strlen(varname) + 1]);
}

int	env_update(char **envp, const char *varname, const char *varvalue)
{
	char	**var;

	var = env_getaddress(envp, varname);
	if (var == NULL || ft_strchr(varname, '='))
		return (-1);
	free(*var);
	*var = ft_strmerge("%s=%s", varname, varvalue);
	return (0);
}
