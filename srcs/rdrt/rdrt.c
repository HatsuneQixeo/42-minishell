/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdrt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:41 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "rdrt.h"

const char	*lstname_rdrt(const char *newname)
{
	static const char	*name = "rdrt";

	if (newname != NULL)
		name = newname;
	return (name);
}

void	lstshow_rdrt(void *content)
{
	const t_rdrt	*rdrt = content;
	char			*padname;

	ft_dprintf(2, "%s: %s: %s\n", lstname_rdrt(NULL),
		rdrt_getvalue(rdrt->ft_rdrt), rdrt->str_arg);
	padname = ft_strmerge("    %s: %s", lstname_rdrt(NULL), lstshow_name(NULL));
	lstshow_tmpname(rdrt->lst_value, lstshow_name,
		padname, lstshow_str);
	free(padname);
}

t_rdrt	*rdrt_new(t_ftrdrt ft_rdrt, char *str_arg)
{
	t_rdrt	*rdrt;

	rdrt = malloc(sizeof(t_rdrt));
	if (rdrt == NULL)
		return (NULL);
	rdrt->ft_rdrt = ft_rdrt;
	rdrt->str_arg = str_arg;
	rdrt->lst_value = NULL;
	return (rdrt);
}

void	del_rdrt(void *content)
{
	t_rdrt	*rdrt;

	rdrt = content;
	free(rdrt->str_arg);
	ft_lstclear(&rdrt->lst_value, free);
	free(rdrt);
}
