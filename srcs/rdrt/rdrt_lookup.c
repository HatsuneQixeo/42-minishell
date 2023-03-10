/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdrt_lookup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/07 15:22:17 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdrt.h"

int	find_rdrtvalue(unsigned int i, const void *arr, const void *value)
{
	const t_rdrt	rdrt = ((const t_rdrt *)arr)[i];

	return (!ft_strcmp(rdrt.str_arg, value));
}

int	find_rdrtft(unsigned int i, const void *arr, const void *ft_rdrt)
{
	const t_rdrt	rdrt = ((const t_rdrt *)arr)[i];

	return (rdrt.ft_rdrt == ft_rdrt);
}

static const t_rdrt	*rdrt_search(t_ftfind ft_find, const void *ref)
{
	static const t_rdrt	arr_rdrt[] = {
	{rdrt_heredoc, "<<", NULL},
	{rdrt_quotedheredoc, "\"<<\"", NULL},
	{rdrt_append, ">>", NULL},
	{rdrt_input, "<", NULL},
	{rdrt_overwrite, ">", NULL},
	};
	static const int	length = (sizeof(arr_rdrt) / sizeof(arr_rdrt[0]));
	const size_t		find = ft_arrfind(arr_rdrt, length, ft_find, ref);

	if (find == SIZE_T_MAX)
		return (NULL);
	else
		return (&arr_rdrt[find]);
}

t_ftrdrt	rdrt_getft(const char *value)
{
	const t_rdrt	*find = rdrt_search(find_rdrtvalue, value);

	if (find == NULL)
		ft_dprintf(2, "rdrt_getft does not recognize: %s\n", value);
	else
		return (find->ft_rdrt);
	return (NULL);
}

const char	*rdrt_getvalue(t_ftrdrt ft_rdrt)
{
	const t_rdrt	*find = rdrt_search(find_rdrtft, ft_rdrt);

	if (find == NULL)
		ft_dprintf(2, "rdrt_getvalue does not recognize: %p\n", ft_rdrt);
	else
		return (find->str_arg);
	return (NULL);
}
