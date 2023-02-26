/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:47:56 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/24 07:52:56 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	@brief Duplicate all strings in envp.
	@note Duplicated strings are stored in double linked list.
 */
t_double_list	*env_init(char **envp)
{
	int				i;
	char			*value;
	t_double_list	*env_list;

	i = -1;
	env_list = NULL;
	while (envp[++i])
	{
		value = ft_strdup(envp[i]);
		double_lstadd_back(&env_list, double_lstnew(value));
	}
	return (env_list);
}

/* 
	@brief Store env_list in static pointer or get env_list.
	@note pass NULL to get env_list and not override the static pointer.
 */
t_double_list	*env_set_or_get(t_double_list *env_head)
{
	static t_double_list	*env_list = NULL;

	if (env_head)
		env_list = env_head;
	return (env_list);
}

/* 
	@brief get env value.
	@note Eg: "PATH=......", return the pointer after "=".
 */
char	*env_value_get(char *env_var)
{
	char			*env_str;
	t_double_list	*env_list;
	int				env_var_len;

	env_var_len = ft_strlen(env_var);
	env_list = env_set_or_get(NULL);
	while (env_list)
	{
			env_str = env_list->content;
		if (!ft_strncmp(env_var, env_str, env_var_len))
			return (env_str + env_var_len + 1);
		env_list = env_list->next;
	}
	return (NULL);
}

void	env_free(t_double_list **env_list)
{
	double_lstclear(env_list, free);
}