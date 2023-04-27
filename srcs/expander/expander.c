/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:41 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "expander.h"

char	*simpleexpand(char **envp, const char *arg)
{
	const char	*var = ft_strchr(arg, '$');
	t_list		*lst_buffer;

	lst_buffer = NULL;
	while (var != NULL)
	{
		if (var != arg)
			ft_lstadd_back(&lst_buffer, ft_lstnew(
					ft_substr(arg, 0, var - arg)));
		ft_lstadd_back(&lst_buffer, ft_lstnew(expand_var(envp, &var)));
		arg = var + 1;
		var = ft_strchr(arg, '$');
	}
	if (var != arg)
		ft_lstadd_back(&lst_buffer, ft_lstnew(ft_strdup(arg)));
	return (ft_lsttostr_clear(&lst_buffer));
}

char	**expand_lst_argv(char **envp, t_list *lst)
{
	t_list	*lst_new;

	lst_new = NULL;
	while (lst != NULL)
	{
		ft_lstadd_back(&lst_new, expand_arg(envp, lst->content));
		lst = lst->next;
	}
	return ((char **)ft_lsttoaa_clear(&lst_new));
}
