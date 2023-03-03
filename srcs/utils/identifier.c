/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:12:49 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/27 16:12:49 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_common.h"

int	ft_isquote(int c)
{
	return (c == '\'' || c == '\"');
}

int	ft_isnameletter(int c)
{
	return (ft_isalnum(c) || c == '_');
}

int	ft_isnameend(int c)
{
	return (c == '\0' || c == '=');
}

int	cmp_strvarname(const void *str, const void *varname)
{
	const char	*it_str = str;
	const char	*it_varname = varname;
	size_t		i;

	i = 0;
	while (it_str[i] == it_varname[i] && !ft_isnameend(it_str[i]))
		i++;
	if (ft_isnameend(it_str[i]) && ft_isnameend(it_varname[i]))
		return (0);
	return (it_str[i] - it_varname[i]);
}
