/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/27 16:12:49 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*heredoc_expand_line(char **envp, const char *str)
{
	t_list		*lst_expanded;
	const char	*ptr_var;

	lst_expanded = NULL;
	while (1)
	{
		ptr_var = ft_strchr(str, '$');
		if (ptr_var == NULL)
			break ;
		ft_lstadd_back(&lst_expanded, ft_lstnew(
				ft_substr(str, 0, ptr_var - str)));
		ft_lstadd_back(&lst_expanded, ft_lstnew(
				expand_var(envp, &ptr_var)));
		str = ptr_var + 1;
	}
	ft_lstadd_back(&lst_expanded, ft_lstnew(ft_strdup(str)));
	return (ft_lsttostr_clear(&lst_expanded));
}

void	heredoc_expand(char **envp, t_list *lst)
{
	char	*tmp;

	while (lst != NULL)
	{
		tmp = lst->content;
		lst->content = heredoc_expand_line(envp, lst->content);
		free(tmp);
		lst = lst->next;
	}
}

char	**expand_lst_argv(char **envp, t_list *lst)
{
	t_list	*lst_new;
	t_token	*token;

	lst_new = NULL;
	while (lst != NULL)
	{
		token = lst->content;
		if (token->type != DEFAULT)
		{
			ms_errlog("Unknown token in expand_lst_argv");
			lstshow_token(token);
		}
		else
			ft_lstadd_back(&lst_new, expand_str(envp, token->value));
		lst = lst->next;
	}
	return ((char **)ft_lsttoaa_clear(&lst_new));
}
