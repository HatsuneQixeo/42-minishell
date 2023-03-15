/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_lookup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:21:25 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:40 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctrl.h"

typedef struct s_ctrlvalue
{
	t_ftctrl	ft_ctrl;
	const char	*value;
}			t_ctrlvalue;

static int	find_ctrlvalue(unsigned int i, const void *arr, const void *name)
{
	const t_ctrlvalue	ctrlvalue = ((const t_ctrlvalue *)arr)[i];

	return (!ft_strcmp(ctrlvalue.value, name));
}

static int	find_ctrlft(unsigned int i, const void *arr, const void *ft_ctrl)
{
	const t_ctrlvalue	ctrlvalue = ((const t_ctrlvalue *)arr)[i];

	return (ctrlvalue.ft_ctrl == ft_ctrl);
}

static const t_ctrlvalue	*ctrl_search(t_ftfind ft_find, const void *ref)
{
	static const t_ctrlvalue	arr_ctrlvalue[] = {
	{.ft_ctrl = ctrl_success, .value = "&&"},
	{.ft_ctrl = ctrl_failure, .value = "||"},
	{.ft_ctrl = ctrl_continue, .value = "|"},
	};
	static const int			length
		= (sizeof(arr_ctrlvalue) / sizeof(arr_ctrlvalue[0]));
	const size_t				find = ft_arrfind(arr_ctrlvalue, length,
			ft_find, ref);

	if (find == SIZE_T_MAX)
		return (NULL);
	else
		return (&arr_ctrlvalue[find]);
}

t_ftctrl	ctrl_getft(const char *value)
{
	const t_ctrlvalue	*find = ctrl_search(find_ctrlvalue, value);

	if (find == NULL)
		ft_dprintf(2, "ctrl_getft does not recognize: %s\n", value);
	else
		return (find->ft_ctrl);
	return (NULL);
}

const char	*ctrl_getvalue(t_ftctrl ft_ctrl)
{
	const t_ctrlvalue	*find = ctrl_search(find_ctrlft, ft_ctrl);

	if (find == NULL)
		ft_dprintf(2, "ctrl_getft does not recognize: %p\n", ft_ctrl);
	else
		return (find->value);
	return (NULL);
}
