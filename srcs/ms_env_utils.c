/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:56:20 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/12/26 17:04:59 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* 
	eg: "PWD=/home/ntan-wan/minishell"
	extract the value after "=".
 */
char	*extract_env_var_value(char *var)
{
	int	str_len;

	if (!var)
		return (NULL);
	str_len = ft_strlen(ft_strchr(var, '=')) + 1;
	return (ft_substr(ft_strchr(var, '='), 1, str_len));
}

/* 
	Iterate environment variables and look for matching var_name.
	Extract env_var value by calling extract_env_var_value().
 */
char	*get_env_var_value(t_env *env, char *var_name)
{
	int	i;

	if (!env || !var_name || !env->vars)
		return (NULL);
	i = -1;
	while (env->vars[++i])
	{
		if (!ft_strncmp(env->vars[i], var_name, ft_strlen(var_name)))
			return (extract_env_var_value(env->vars[i]));
	}
	return (NULL);
}

t_env	*ms_init_env(char **envp)
{
	t_env	*env;

	if (!envp)
		return (NULL);
	env = ft_calloc(1, sizeof(t_env));
	if (env)
	{
		env->envp = envp;
		env->vars = util_str_arr_dup(envp);
		env->pwd = get_env_var_value(env, "PWD");
		env->oldpwd = get_env_var_value(env, "OLDPWD");
	}
	return (env);
}

void	env_free(t_env **environment)
{
	int		i;
	t_env	*env;

	i = -1;
	env = *environment;
	if (!env)
		return ;
	while (env->vars && env->vars[++i])
		free(env->vars[i]);
	free(env->vars);
	free(env->pwd);
	free(env->oldpwd);
	free(env);
	*environment = NULL;
}
