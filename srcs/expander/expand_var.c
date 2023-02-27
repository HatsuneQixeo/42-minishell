/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/27 16:12:49 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_common.h"

char	*ft_getenv(char **envp, const char *varname)
{
	char	*var_joined;
	size_t	len_varname;

	var_joined = ft_strjoin(varname, "=");
	len_varname = ft_strlen(var_joined);
	while (*envp != NULL && ft_strncmp(*envp, var_joined, len_varname))
		envp++;
	free(var_joined);
	if (*envp == NULL)
		return (NULL);
	else
		return ((*envp) + len_varname);
}

static size_t	shell_varname_len(const char *src)
{
	size_t	i;

	i = 0;
	while (ft_isnameletter(src[i]))
		i++;
	return (i);
}

/**
 * @brief Substr the $MIKU from "$MIKU/iscute"
 * 
 * @param src ptr to '$'
 * @return char* $MIKU/iscute -> MIKU
 * @bug It will assume the first character is '$'
 * 	and not do any additional checking
 */
static char	*ms_substr_varname(const char *src)
{
	return (ft_substr(&src[1], 0, shell_varname_len(&src[1])));
}

/**
 * @brief Substr the env value of the given str,
 * 	also move the ptr to the end of the variable name
 * 
 * @param envp 
 * @param p_it 
 * @return char* 
 */
static char	*ft_substrenv(char **envp, const char **p_it)
{
	char	*str_varname;
	char	*str_varvalue;

	str_varname = ms_substr_varname(*p_it);
	(*p_it) += ft_strlen(str_varname);
	str_varvalue = ft_getenv(envp, str_varname);
	free(str_varname);
	if (str_varvalue == NULL)
		return (NULL);
	else
		return (ft_strdup(str_varvalue));
}

/**
 * @brief For expanding an iterator pointing to '$' character
 * 
 * @param envp 
 * @param p_it 
 * @return char* 
 */
char	*expand_var(char **envp, const char **p_it)
{
	const char	chr = (*p_it)[1];

	if ((*p_it)[0] != '$')
	{
		ft_dprintf(2, "expand_var is called"
			"when the first character is not `$': %s\n", *p_it);
		return (NULL);
	}
	else if (chr == '?')
	{
		(*p_it)++;
		return (ft_itoa(g_lastexit));
	}
	else if (ft_isquote(chr))
		return (ft_strdup(""));
	else if (!ft_isnameletter(chr))
		return (ft_strdup("$"));
	else if (ft_isdigit(chr))
	{
		(*p_it)++;
		return (ft_strdup(""));
	}
	else
		return (ft_substrenv(envp, p_it));
}
