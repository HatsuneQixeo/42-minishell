/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_log.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:12:48 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:39 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ms_common.h"

static void	iteri_sortinsert_nameascend(unsigned int i, void *strlist)
{
	char	**p_it;

	p_it = strlist;
	while (i-- && cmp_strvarname(p_it[i], p_it[i + 1]) > 0)
		ft_memswap(&p_it[i], &p_it[i + 1], sizeof(char *));
}

static void	iteri_logexport(unsigned int i, void *envp)
{
	const char	*env = ((const char **)envp)[i];
	const char	*assignment = ft_strchr(env, '=');

	if (assignment != NULL)
		ft_printf("declare -x %.*s=\"%s\"\n",
			assignment - env, env, assignment + 1);
	else
		ft_printf("declare -x %s\n", env);
}

void	export_log(char **envp)
{
	char	**env_declaration;

	env_declaration = (char **)ft_aamap((void **)envp, map_copy, NULL);
	ft_aaiteri(env_declaration, iteri_sortinsert_nameascend);
	ft_aaiteri(env_declaration, iteri_logexport);
	free(env_declaration);
}
